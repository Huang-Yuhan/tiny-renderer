/**
 * @file LineShader.h
 * @author icecream_sarkaz
 * @brief 
 * @version 0.1
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 * @brief
 * 一个简单的线段着色器
 * 只渲染线段
 * 这一部分主要是为了测试vertex shader的正确性
 */

#include "IShader.h"
#pragma once



class LineShader:public IShaderSpace::IShader
{
private:
    /* data */
    
public:
    LineShader()=default;
    ~LineShader()=default;
    /**
     * @brief 
     * 
     * @param vertex 3D空间中的顶点
     * @return IShaderSpace::Vertex_Type 返回屏幕空间中的顶点(包括z坐标信息，用于深度测试)
     */
    IShaderSpace::Vertex_Type vertex_shader(IShaderSpace::Vertex_Type vertex)override
    {
        //Vertex_Type  = vec3
        IShaderSpace::homogenous_Vertex_Type homogenous_vertex=IShaderSpace::homogenous_Vertex_Type(vertex,1.0f);
        IShaderSpace::homogenous_Vertex_Type res = ViewportTransformMatrix*projectionTransformMatrix*viewTransformMatrix*modelTransformMatrix*homogenous_vertex;
        return IShaderSpace::Vertex_Type(res.x/res.w,res.y/res.w,res.z/res.w);
    }
    /**
     * @brief 
     * 只是简单地继承，LineShader中不实现fragment shader 
     */
    void fragment_shader(IShaderSpace::Light_Type light,IShaderSpace::Noraml_Type normal,TGAColor &color)override
    {
        /*在LineShader中不实现fragment shader*/
        color=TGAColor(255,255,255,255);
    }
    
};

