/**
 * @file LineRenderer.h
 * @author icecream_sarkaz
 * @brief 
 * @version 0.1
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "LineShader.h"
#include "SimpleCamera.h"
#include "ObjModel.h"
#include "tgaimage.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include <memory>

class LineRenderer
{
private:
    /*data*/
    int width,height;
    double nearPlane;
    double farPlane;
    double fov;
    std::string filePath;
    std::unique_ptr<IShaderSpace::IShader> shader;
    std::unique_ptr<ICameraSpace::ICamera> camera;
    std::unique_ptr<IModelSpace::IModel> model;
    TGAImage image;
    /*function*/
    IShaderSpace::Matrix_Type GetPerspective();
    IShaderSpace::Matrix_Type GetViewport();
    void drawLine(double x0,double y0,double x1,double y1);
public:
    LineRenderer(int width,int height,std::string filePath);
    void init();
    void render();
    void TestInfo();
    
};

LineRenderer::LineRenderer(int width,int height,std::string filePath):
width(width),height(height),filePath(filePath)
{
    shader=std::make_unique<LineShader>();
    camera=std::make_unique<SimpleCamera>();
    model=std::make_unique<IModelSpace::ObjModel>();
    model->readModel(filePath);
    image=TGAImage(width,height,TGAImage::RGB);
    nearPlane=0.1;
    farPlane=1000;
}

/**
 * @brief 
 * 在render前的一些准备工作
 */
void LineRenderer::init()
{
    //set camera
    camera->setCameraPosition(glm::vec3(0.0f,5.0f,0.0f));
    camera->setCameraDirection(glm::normalize(camera->getCameraPosition()));
    constexpr glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
    camera->setCameraRight(glm::normalize(glm::cross(up,camera->getCameraUp())));
    camera->setCameraUp(glm::normalize(glm::cross(camera->getCameraRight(),camera->getCameraDirection())));

    //set shader
    shader->modelTransformMatrix=glm::mat4(1.0f);
    shader->viewTransformMatrix=camera->GetLookAt();
    shader->projectionTransformMatrix=GetPerspective();
    shader->ViewportTransformMatrix=GetViewport();
}

/**
 * @brief 
 * 
 * render
 * 
 */
void LineRenderer::render()
{
    for(int i=0;i<model->faces.size();i++)
    {
        for(int j=0;j<3;j++)
        {
            IModelSpace::Vertex_Type v0=model->vertices[std::get<0>(model->faces[i])[j]];
            IModelSpace::Vertex_Type v1=model->vertices[std::get<1>(model->faces[i])[j]];
            IModelSpace::Vertex_Type v2=model->vertices[std::get<2>(model->faces[i])[j]];

            IShaderSpace::Vertex_Type sv0=shader->vertex_shader(v0);
            IShaderSpace::Vertex_Type sv1=shader->vertex_shader(v1);
            IShaderSpace::Vertex_Type sv2=shader->vertex_shader(v2);

            drawLine(sv0.x,sv0.y,sv1.x,sv1.y);
            drawLine(sv1.x,sv1.y,sv2.x,sv2.y);
            drawLine(sv2.x,sv2.y,sv0.x,sv0.y);
        }
    }

}

/**
 * @brief 
 * init the perspective matrix
 */
IShaderSpace::Matrix_Type LineRenderer::GetPerspective()
{
    ICameraSpace::mat projectionMatrix;
    double aspectRatio=width/height;
    double r = nearPlane * tan(fov / 2);
    projectionMatrix[0][0] = 1/r;
    projectionMatrix[1][1] = aspectRatio/r;
    projectionMatrix[2][2] = (nearPlane + farPlane) / (nearPlane - farPlane);
    projectionMatrix[2][3] = -1;
    projectionMatrix[3][2] = 2 * nearPlane * farPlane / (nearPlane - farPlane);

    return projectionMatrix;
}

/**
 * @brief 
 * init the viewport matrix
 */
IShaderSpace::Matrix_Type LineRenderer::GetViewport()
{
    ICameraSpace::mat viewportMatrix;
    viewportMatrix[0][0] = width / 2.0f;
    viewportMatrix[1][1] = height / 2.0f;
    viewportMatrix[2][2] = (farPlane-nearPlane)/ 2.0f;
    viewportMatrix[3][0] = width / 2.0f;
    viewportMatrix[3][1] = height / 2.0f;
    viewportMatrix[3][2] = (farPlane+nearPlane)/ 2.0f;
    return viewportMatrix;
}

void LineRenderer::drawLine(double x0,double y0,double x1,double y1)
{
    std::cout<<"writing a line from ("<<x0<<","<<y0<<") to ("<<x1<<","<<y1<<")"<<std::endl;

    //double t belongs to [0,1]
    int dx,dy;
    dx=x1-x0;
    dy=y1-y0;
    if(std::abs(dx)>std::abs(dy))
    {
        double xincr=1.0*dx/std::abs(dx);
        double yincr=1.0*dy/std::abs(dx);
        double x=x0,y=y0;
        for(int t=std::abs(dx);t>0;t--)
        {
            image.set(x,y,TGAColor(255,255,255,255));
            x+=xincr;
            y+=yincr;
            std::cout<<"("<<x<<","<<y<<")"<<std::endl;
        }
    }
    else
    {
        double xincr=dx/std::abs(dy);
        double yincr=dy/std::abs(dy);
        double x=x0,y=y0;
        for(int t=std::abs(dy);t>0;t--)
        {
            image.set(x,y,TGAColor(255,255,255,255));
            x+=xincr;
            y+=yincr;
            std::cout<<"("<<x<<","<<y<<")"<<std::endl;
        }
    }
}

/**
 * @brief 输出一些测试信息
 * 
 */
void LineRenderer::TestInfo()
{
    //输出在Linerenderer中的矩阵
    std::cout<<"Matrices in LineRenderer:"<<std::endl;
    //perspective matrix
    std::cout<<"perspective matrix:"<<std::endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            std::cout<<shader->projectionTransformMatrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    //viewport matrix
    std::cout<<"viewport matrix:"<<std::endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            std::cout<<shader->ViewportTransformMatrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    //viewTransformMatrix
    std::cout<<"viewTransformMatrix:"<<std::endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            std::cout<<shader->viewTransformMatrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    //用glm构造出来的矩阵
    std::cout<<"Matrices in glm:"<<std::endl;
    //perspective matrix
    std::cout<<"perspective matrix:"<<std::endl;
    auto glm_perspective=glm::perspective(glm::radians(fov),width/height*1.0,nearPlane*1.0,1.0*farPlane);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            std::cout<<glm_perspective[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    //viewport matrix
    std::cout<<"viewport matrix:"<<std::endl;
    auto glm_viewport=glm::mat4(1.0);
    glm_viewport[0][0]=width/2.0;
    glm_viewport[1][1]=height/2.0;
    glm_viewport[2][2]=(farPlane-nearPlane)/2.0;
    glm_viewport[3][0]=width/2.0;
    glm_viewport[3][1]=height/2.0;
    glm_viewport[3][2]=(farPlane+nearPlane)/2.0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            std::cout<<glm_viewport[i][j]<<" ";
        }
        std::cout<<std::endl;
    }


    //viewTransformMatrix
    std::cout<<"viewTransformMatrix:"<<std::endl;
    auto glm_lookat=glm::lookAt(camera->getCameraPosition(),glm::vec3(0,0,0),camera->getCameraUp());
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            std::cout<<glm_lookat[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    shader->projectionTransformMatrix=glm_perspective;
    shader->ViewportTransformMatrix=glm_viewport;
    shader->viewTransformMatrix=glm_lookat;
    render();
}