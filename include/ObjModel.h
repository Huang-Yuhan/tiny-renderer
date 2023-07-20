#include "IModel.h"
#include<vector>
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>
#include<fstream>
#include<iostream>
#include<memory>
#pragma once

namespace IModelSpace
{

    /**
     * @brief
     * obj文件读取
     * v : 顶点坐标
     * vt : 贴图的坐标点
     * vn : 法向量
     * f : 面 后面3个参数是：       顶点/贴图uv/法向量  参数为索引值
     */


    /**
     * @brief
     * 读取.obj文件
     */
    class ObjModel:public IModel
    {
    private:

    public:
        /**
         * @brief
         * read Model File
         *
         * @param filePath
         */
        ObjModel()=default;
        ~ObjModel()=default;
        void readModel(const std::string &filePath) override
        {
            std::ifstream fin;
            fin.open(filePath);
            if(fin.fail())
            {
                std::cout<< "read model file fail !!\n\n";
                exit(0);
            }

            std::string type;
            float fparam[3];
            int iparam[3];
            while(fin>>type)
            {
                if( type == "v" )
                {
                    for(int i=0;i<3;i++)fin>>fparam[i];
                    vertices.emplace_back(fparam[0],fparam[1],fparam[2]);
                }
                else if ( type == "vn")
                {
                    for(int i=0;i<3;i++)fin>>fparam[i];
                    normals.emplace_back(fparam[0],fparam[1],fparam[2]);
                }
                else if ( type == "f")
                {
                    glm::ivec3 faceParam[3];
                    for(int i=0;i<3;i++)
                    {
                        std::string s;
                        fin>>s;
                        sscanf(s.c_str(),"%d/%d/%d",&iparam[0],&iparam[1],&iparam[2]);
                        faceParam[i] = glm::ivec3(iparam[0],iparam[1],iparam[2]);
                    }
        
                    faces.emplace_back(faceParam[0],faceParam[1],faceParam[2]);
                }
                else if ( type == "vt")
                {
                    for(int i=0;i<2;i++)fin>>fparam[i];
                    uvs.emplace_back(fparam[0],fparam[1]);
                }
            }

            //输出读取的数据
            /*
            std::cout<<"read file success !!\n"<<std::endl;
            std::cout<<"file name : "<<filePath<<std::endl<<std::endl;
            std::cout<<"vertices size: "<<vertices.size()<<std::endl<<std::endl;
            std::cout<<"vertices are :"<<std::endl<<std::endl;
            for(auto &v:vertices)
            {
                std::cout<<v.x<<" "<<v.y<<" "<<v.z<<std::endl;
            }
            std::cout<<"normals size: "<<normals.size()<<std::endl<<std::endl;
            std::cout<<"normals are :"<<std::endl<<std::endl;
            for(auto &v:normals)
            {
                std::cout<<v.x<<" "<<v.y<<" "<<v.z<<std::endl;
            }

            std::cout<<"uvs size: "<<uvs.size()<<std::endl<<std::endl;
            std::cout<<"uvs are :"<<std::endl<<std::endl;
            for(auto &v:uvs)
            {
                std::cout<<v.x<<" "<<v.y<<std::endl;
            }

            std::cout<<"faces size: "<<faces.size()<<std::endl<<std::endl;
            std::cout<<"faces are :"<<std::endl<<std::endl;
            for(auto &v:faces)
            {
                std::cout<<std::get<0>(v)[0]<<"/"<<std::get<0>(v)[1]<<"/"<<std::get<0>(v)[2]<<" ";
                std::cout<<std::get<1>(v)[0]<<"/"<<std::get<1>(v)[1]<<"/"<<std::get<1>(v)[2]<<" ";
                std::cout<<std::get<2>(v)[0]<<"/"<<std::get<2>(v)[1]<<"/"<<std::get<2>(v)[2]<<std::endl;
            }
            */

        }
    };

}