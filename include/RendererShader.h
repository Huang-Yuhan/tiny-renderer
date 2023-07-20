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
        float intensity=glm::dot(normal,light);
        color=TGAColor(255*intensity,255*intensity,255*intensity,255);
    }
};