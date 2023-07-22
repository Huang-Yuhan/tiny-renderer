#include "IShader.h"
#pragma once

class RendererShader:public IShaderSpace::IShader
{
    IShaderSpace::Vertex_Type vertex_shader(IShaderSpace::Vertex_Type vertex)override
    {
        IShaderSpace::homogenous_Vertex_Type homogenous_vertex=IShaderSpace::homogenous_Vertex_Type(vertex,1.0f);
        IShaderSpace::homogenous_Vertex_Type res = ViewportTransformMatrix*projectionTransformMatrix*viewTransformMatrix*modelTransformMatrix*homogenous_vertex;
        return IShaderSpace::Vertex_Type(res.x/res.w,res.y/res.w,res.z/res.w);    
    }
    void fragment_shader(IShaderSpace::Light_Type light,IShaderSpace::Noraml_Type normal,TGAColor &color)override
    {

        IShaderSpace::Noraml_Type n = IShaderSpace::Noraml_Type(glm::normalize(uniform_MIT * glm::vec4(normal, 0.0)));
        IShaderSpace::Light_Type l = IShaderSpace::Light_Type(glm::normalize(uniform_M * glm::vec4(light, 0.0)));

        double intensity=glm::dot(n,l);
        if(intensity<0)intensity =0;
        //std::cout<<"intensity:"<<intensity<<std::endl;
        color[0] = color[0]*intensity;
        color[1] = color[1]*intensity;
        color[2] = color[2]*intensity;
    }
};