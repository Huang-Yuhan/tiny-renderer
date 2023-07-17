/**
 * @file LineRenderer.h
 * @author icecream_sarkaz
 * @brief 
 * @version 0.1
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * ! PerspectiveMatrix Error!!!!
 * ! viewTransformMatrix Error!!!!
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
    std::unique_ptr<TGAImage> image;
    /*function*/
    IShaderSpace::Matrix_Type GetPerspective();
    IShaderSpace::Matrix_Type GetViewport();
    void drawLine(int x0,int y0,int x1,int y1);
public:
    LineRenderer(int width,int height,std::string filePath);
    void init();
    void render();
    void TestInfo();
    void checkMatrixEqual();
};

LineRenderer::LineRenderer(int width,int height,std::string filePath):
width(width),height(height),filePath(filePath)
{
    shader=std::make_unique<LineShader>();
    camera=std::make_unique<SimpleCamera>();
    model=std::make_unique<IModelSpace::ObjModel>();
    model->readModel(filePath);
    image=std::make_unique<TGAImage>(width,height,TGAImage::RGB);
    nearPlane=0.1;
    farPlane=100;
    fov=50;
}

/**
 * @brief 
 * 在render前的一些准备工作
 */
void LineRenderer::init()
{
    //set camera
    camera->setCameraPosition(glm::vec3(3.0f,.0f,3.0f));
    camera->setCameraTarget(glm::vec3(0.0f,0.0f,0.0f));
    camera->initVector();


    //set shader
    shader->modelTransformMatrix=glm::mat4(1.0f);
    shader->viewTransformMatrix=camera->GetLookAt();
    shader->projectionTransformMatrix=GetPerspective();
    shader->ViewportTransformMatrix=GetViewport();

    checkMatrixEqual();

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
        IModelSpace::Vertex_Type v0=model->vertices[std::get<0>(model->faces[i])[0]-1];
        IModelSpace::Vertex_Type v1=model->vertices[std::get<1>(model->faces[i])[0]-1];
        IModelSpace::Vertex_Type v2=model->vertices[std::get<2>(model->faces[i])[0]-1];

        IShaderSpace::Vertex_Type sv0=shader->vertex_shader(v0);
        IShaderSpace::Vertex_Type sv1=shader->vertex_shader(v1);
        IShaderSpace::Vertex_Type sv2=shader->vertex_shader(v2);

        drawLine(sv0.x,sv0.y,sv1.x,sv1.y);
        drawLine(sv1.x,sv1.y,sv2.x,sv2.y);
        drawLine(sv2.x,sv2.y,sv0.x,sv0.y);
    }
    image->write_tga_file("LineRenderer_output.tga");
}

/**
 * @brief 
 * init the perspective matrix
 */
IShaderSpace::Matrix_Type LineRenderer::GetPerspective()
{
    ICameraSpace::mat projectionMatrix=ICameraSpace::mat(1.0f);
    double aspectRatio=1.0*width/height;
    double tanHalfFov=tan(glm::radians(fov)/2);             //radians是线性函数，将角度转化为弧度
    projectionMatrix[0][0] = 1/(aspectRatio*tanHalfFov);
    projectionMatrix[1][1] =  1/tanHalfFov;
    projectionMatrix[2][2] = (nearPlane + farPlane) / (nearPlane - farPlane);
    projectionMatrix[2][3] = -1;
    projectionMatrix[3][2] = 2 * nearPlane * farPlane / (nearPlane - farPlane);
    projectionMatrix[3][3] = 0;

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

void LineRenderer::drawLine(int x0,int y0,int x1,int y1)
{
    std::cout<<"writing a line from ("<<x0<<","<<y0<<") to ("<<x1<<","<<y1<<")"<<std::endl;

    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image->set(y, x, TGAColor(255, 255, 255,255));
        } else {
            image->set(x, y, TGAColor(255, 255, 255,255));
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
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
    auto glm_perspective=glm::perspective(glm::radians(fov),1.0*width/height,nearPlane,farPlane);
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
    auto glm_lookat=glm::lookAt(camera->getCameraPosition(),glm::vec3(0,0,0),glm::vec3(0,1,0));
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            std::cout<<glm_lookat[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    /*
    shader->projectionTransformMatrix=glm_perspective;
    shader->ViewportTransformMatrix=glm_viewport;
    shader->viewTransformMatrix=glm_lookat;
    std::cout<<"TestInfo ready to renderer"<<std::endl<<std::endl;
    render();*/
}

void LineRenderer::checkMatrixEqual()
{
    auto glm_lookat=glm::lookAt(camera->getCameraPosition(),glm::vec3(0,0,0),glm::vec3(0,1,0));
    auto glm_perspective=glm::perspective(glm::radians(fov),1.0*width/height,nearPlane,farPlane);
    auto glm_viewport=glm::mat4(1.0);
    glm_viewport[0][0]=width/2.0;
    glm_viewport[1][1]=height/2.0;
    glm_viewport[2][2]=(farPlane-nearPlane)/2.0;
    glm_viewport[3][0]=width/2.0;
    glm_viewport[3][1]=height/2.0;
    glm_viewport[3][2]=(farPlane+nearPlane)/2.0;

    bool flag=true;

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            if(std::abs(glm_lookat[i][j]-shader->viewTransformMatrix[i][j])>0.0001)
            {
                flag=false;
                std::cout<<"viewTransformMatrix not equal"<<std::endl;
                std::cout<<"glm:"<<glm_lookat[i][j]<<" shader:"<<shader->viewTransformMatrix[i][j]<<std::endl;
            }
            if(std::abs(glm_perspective[i][j]-shader->projectionTransformMatrix[i][j])>0.0001)
            {
                flag=false;
                std::cout<<"projectionTransformMatrix not equal"<<std::endl;
                std::cout<<"glm:"<<glm_perspective[i][j]<<" shader:"<<shader->projectionTransformMatrix[i][j]<<std::endl;
            }
            if(std::abs(glm_viewport[i][j]-shader->ViewportTransformMatrix[i][j])>0.0001)
            {
                flag=false;
                std::cout<<"ViewportTransformMatrix not equal"<<std::endl;
                std::cout<<"glm:"<<glm_viewport[i][j]<<" shader:"<<shader->ViewportTransformMatrix[i][j]<<std::endl;
            }

        }
    if(!flag)TestInfo();
}