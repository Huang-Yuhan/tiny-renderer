#include<glm/vec3.hpp>
#include<glm/matrix.hpp>
#include"tgaimage.h"
#include<iostream>
#pragma once

namespace IShaderSpace
{

    typedef glm::vec3 Light_Type;
    typedef glm::vec3 Vertex_Type;
    typedef glm::mat4 Matrix_Type;
    typedef glm::vec4 homogenous_Vertex_Type;
    typedef glm::vec3 Noraml_Type;
    /**
     * @brief
     * Shader的抽象类
     */
    class IShader
    {
        public:

        Matrix_Type uniform_MIT;
        Matrix_Type uniform_M;
        /*data*/
        Matrix_Type modelTransformMatrix;
        Matrix_Type viewTransformMatrix;
        Matrix_Type projectionTransformMatrix;
        Matrix_Type ViewportTransformMatrix;
        virtual Vertex_Type vertex_shader(Vertex_Type vertex)=0;
        virtual void fragment_shader(Light_Type light,Noraml_Type normal,TGAColor &color)=0;
        void outputMatrix()
        {
            std::cout<<"output matrices"<<std::endl;
            std::cout<<"<------------------------------------------------------->"<<std::endl;
            
            std::cout<<"modelTransformMatrix"<<std::endl;
            for(int j=0;j<4;j++)
            {
                for(int i=0;i<4;i++)
                {
                    std::cout<<modelTransformMatrix[i][j]<<" ";
                }
                std::cout<<std::endl;
            }

            std::cout<<"viewTransformMatrix"<<std::endl;
            for(int j=0;j<4;j++)
            {
                for(int i=0;i<4;i++)
                {
                    std::cout<<viewTransformMatrix[i][j]<<" ";
                }
                std::cout<<std::endl;
            }

            std::cout<<"projectionTransformMatrix"<<std::endl;

            for(int j=0;j<4;j++)
            {
                for(int i=0;i<4;i++)
                {
                    std::cout<<projectionTransformMatrix[i][j]<<" ";
                }
                std::cout<<std::endl;
            }

            std::cout<<"ViewportTransformMatrix"<<std::endl;

            for(int j=0;j<4;j++)
            {
                for(int i=0;i<4;i++)
                {
                    std::cout<<ViewportTransformMatrix[i][j]<<" ";
                }
                std::cout<<std::endl;
            }

            std::cout<<"<------------------------------------------------------->"<<std::endl;
        }
    };

}