/**
 * @file Renderer.h
 * @author your name (you@domain.com)
 * @brief 
 * 可以设置不同的shader
 * @version 0.1
 * @date 2023-07-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "IShader.h"
#include "LineShader.h"
#include "SimpleCamera.h"
#include "ObjModel.h"
#include "tgaimage.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<limits>
#pragma once

class Renderer
{
private:
    int width,height;   //屏幕宽高
    double nearPlane;   //近平面
    double farPlane;    //远平面
    double fov;         //视角

    std::string filePath;   //模型文件路径
    
    std::unique_ptr<ICameraSpace::ICamera> camera;    //相机
    std::unique_ptr<IModelSpace::IModel> model;       //模型
    std::unique_ptr<TGAImage> image;                  //图像
    /**
     * @brief 
     * 这里使用shared_ptr是为了方便设置不同的shader
     */
    std::shared_ptr<IShaderSpace::IShader> shader;

    std::vector<double> depth;                           //深度缓存
    std::vector<TGAColor> zbuffer;                    //zbuffer;

    IShaderSpace::Matrix_Type getPerspective();
    IShaderSpace::Matrix_Type getViewport();
    void drawTriangle(IModelSpace::Face_Type face);
    inline glm::vec3 getBaryCentric(glm::vec2 a,glm::vec2 b,glm::vec2 c,glm::vec2 vertex);
public:
    Renderer(int width,int height,std::string filePath);
    void render();
    void setShader(std::shared_ptr<IShaderSpace::IShader> shader);
};

/**
 * @brief Construct a new Renderer:: Renderer object
 * constru
 * @param width 
 * @param height 
 * @param filePath 
 */
Renderer::Renderer(int width,int height,std::string filePath):
width(width),height(height),filePath(filePath)
{
    camera=std::make_unique<SimpleCamera>();
    model=std::make_unique<IModelSpace::ObjModel>();
    model->readModel(filePath);
    image=std::make_unique<TGAImage>(width,height,TGAImage::RGB);
    nearPlane=0.1;
    farPlane=100;
    fov=50;

    //默认shader
    shader=std::make_shared<LineShader>();

    //set camera
    camera->setCameraPosition(glm::vec3(3,0,3));
    camera->setCameraTarget(glm::vec3(0,0,0));
    camera->initVector();


}
/**
 * @brief 
 * set shader 
 * @param shader 
 */
void Renderer::setShader(std::shared_ptr<IShaderSpace::IShader> shader)
{
    this->shader=shader;
}

IShaderSpace::Matrix_Type Renderer::getPerspective()
{
    IShaderSpace::Matrix_Type projectionMatrix = IShaderSpace::Matrix_Type(1.0f);
    double aspectRatio = 1.0*width/height;
    //由于radians是线性函数，所以/2在里面或者在外面都可以
    double tanHalfFov = tan(glm::radians(fov)/2);
    projectionMatrix[0][0] = 1/(aspectRatio* tanHalfFov);
    projectionMatrix[1][1] = 1/tanHalfFov;
    projectionMatrix[2][2] = (nearPlane+farPlane)/(nearPlane-farPlane);
    projectionMatrix[2][3] =-1;
    projectionMatrix[3][2] = 2*nearPlane*farPlane/(nearPlane-farPlane);
    projectionMatrix[3][3] =0;
    
    return projectionMatrix;
}

IShaderSpace::Matrix_Type Renderer::getViewport(){
    IShaderSpace::Matrix_Type viewportMatrix;
    viewportMatrix[0][0] = width / 2.0f;
    viewportMatrix[1][1] = height / 2.0f;
    viewportMatrix[2][2] = (farPlane-nearPlane)/ 2.0f;
    viewportMatrix[3][0] = width / 2.0f;
    viewportMatrix[3][1] = height / 2.0f;
    viewportMatrix[3][2] = (farPlane+nearPlane)/ 2.0f;
    return viewportMatrix;
}

void Renderer::render()
{

    //set zbuffer

    depth.resize(width*height,std::numeric_limits<int>::min());        //?
    zbuffer.resize(width*height,TGAColor(0,0,0,0));

    shader->modelTransformMatrix = glm::mat4(1.0f);
    shader->viewTransformMatrix = camera->GetLookAt();
    shader->projectionTransformMatrix = getPerspective();
    shader->ViewportTransformMatrix = getViewport();

    shader->outputMatrix();

    //ready to render

    for(int i=0;i<model->faces.size();i++)drawTriangle(model->faces[i]);


    //save image
    for(int x=0;x<width;x++)
        for(int y=0;y<height;y++)
            image->set(x,y,zbuffer[x+y*width]);

    image->write_tga_file("renderer.tga");

}

void Renderer::drawTriangle(IModelSpace::Face_Type face)
{
    IModelSpace::Vertex_Type v0 = model->vertices[std::get<0>(face)[0]-1];
    IModelSpace::Vertex_Type v1 = model->vertices[std::get<1>(face)[0]-1];
    IModelSpace::Vertex_Type v2 = model->vertices[std::get<2>(face)[0]-1];

    IModelSpace::UV_Type uv0 = model->uvs[std::get<0>(face)[1]-1];
    IModelSpace::UV_Type uv1 = model->uvs[std::get<1>(face)[1]-1];
    IModelSpace::UV_Type uv2 = model->uvs[std::get<2>(face)[1]-1];

    IModelSpace::Normal_Type n0 = model->normals[std::get<0>(face)[2]-1];
    IModelSpace::Normal_Type n1 = model->normals[std::get<1>(face)[2]-1];
    IModelSpace::Normal_Type n2 = model->normals[std::get<2>(face)[2]-1];

    IShaderSpace::Vertex_Type screenVertex0 = shader->vertex_shader(v0);
    IShaderSpace::Vertex_Type screenVertex1 = shader->vertex_shader(v1);
    IShaderSpace::Vertex_Type screenVertex2 = shader->vertex_shader(v2);
    /*
    //debug,高亮点
    for(int x = screenVertex0.x-20;x<=screenVertex0.x+20;x++)
        for(int y = screenVertex0.y-20;y<=screenVertex0.y+20;y++)
            zbuffer[x+y*width] = TGAColor(255,255,0,255);
    for(int x = screenVertex1.x-20;x<=screenVertex1.x+20;x++)
        for(int y = screenVertex1.y-20;y<=screenVertex1.y+20;y++)
            zbuffer[x+y*width] = TGAColor(255,255,0,255);
    for(int x = screenVertex2.x-20;x<=screenVertex2.x+20;x++)
        for(int y = screenVertex2.y-20;y<=screenVertex2.y+20;y++)
            zbuffer[x+y*width] = TGAColor(255,255,0,255);*/

    //计算三角形的包围盒

    int minX = std::min(screenVertex0.x,std::min(screenVertex1.x,screenVertex2.x));
    int maxX = std::max(screenVertex0.x,std::max(screenVertex1.x,screenVertex2.x));
    int minY = std::min(screenVertex0.y,std::min(screenVertex1.y,screenVertex2.y));
    int maxY = std::max(screenVertex0.y,std::max(screenVertex1.y,screenVertex2.y));

    //裁剪

    minX = std::max(0,minX);
    maxX = std::min(width-1,maxX);
    minY = std::max(0,minY);
    maxY = std::min(height-1,maxY);

    //遍历包围盒内的像素

    for(int x=minX;x<=maxX;x++)
    {
        for(int y=minY;y<=maxY;y++)
        {

            int idx = x*width+y;

            //计算重心坐标(注意插值矫正,我们所用的重心坐标应该是在世界空间下的重心坐标)
            //先计算屏幕坐标下的重心坐标
            glm::vec3 baryCentric = getBaryCentric(glm::vec2(screenVertex0.x,screenVertex0.y),glm::vec2(screenVertex1.x,screenVertex1.y),glm::vec2(screenVertex2.x,screenVertex2.y),glm::vec2(x,y));
            //如果重心坐标有一个小于0,说明这个点在三角形外面
            if(baryCentric.x<0||baryCentric.y<0||baryCentric.z<0)continue;
            //!透视矫正出现问题
            /*//计算世界坐标下的深度插值
            float z = 1/(baryCentric[0]/v0.z+baryCentric[1]/v1.z+baryCentric[2]/v2.z);
            //如果深度小于缓存中的值，说明被覆盖掉了
            if(z<depth[idx])
            {
                continue;
            }
            //计算法向量插值
            IModelSpace::Normal_Type normal = (baryCentric[0]/v0.z*n0+baryCentric[1]/v1.z*n1+baryCentric[2]/v2.z*n2)*z;
            //计算uv坐标插值
            IModelSpace::UV_Type uv = (baryCentric[0]/v0.z*uv0+baryCentric[1]/v1.z*uv1+baryCentric[2]/v2.z*uv2)*z;\
            //TODO:从uv图中获取颜色，然后传入到fragment shader中
            //计算颜色插值
            TGAColor color(0,0,0,0);
            //计算光照
            const glm::vec3 lightDir = glm::normalize(glm::vec3(0,-1,-1));
            shader->fragment_shader(-lightDir,normal,color);
            //写入颜色
            depth[idx] = z;
            zbuffer[idx] = color;*/
            float z =baryCentric[0]*v0.z+baryCentric[1]*v1.z+baryCentric[2]*v2.z;
            if(z<depth[idx])continue;
            IModelSpace::Normal_Type normal = baryCentric[0]*n0+baryCentric[1]*n1+baryCentric[2]*n2;
            TGAColor color(0,0,0,0);
            const glm::vec3 lightDir = glm::normalize(glm::vec3(0,-1,-1));
            shader->fragment_shader(-lightDir,normal,color);
            depth[idx] = z;
            zbuffer[idx] = color;

        }
    }

}

inline glm::vec3 Renderer::getBaryCentric(glm::vec2 a,glm::vec2 b,glm::vec2 c,glm::vec2 vertex)
{
    float alpha,beta,gamma;
    gamma = ((a.y-b.y)*vertex.x+(b.x-a.x)*vertex.y+a.x*b.y-b.x*a.y) / ((a.y-b.y)*c.x+(b.x-a.x)*c.y+a.x*b.y-b.x*a.y);
    beta = ((a.y-c.y)*vertex.x+(c.x-a.x)*vertex.y+a.x*c.y-c.x*a.y) / ((a.y-c.y)*b.x+(c.x-a.x)*b.y+a.x*c.y-c.x*a.y);
    alpha = 1 - beta - gamma;

    return glm::vec3(alpha,beta,gamma);
}