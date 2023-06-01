#include "IModel.h"
#include<vector>
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>
#include<fstream>
#include<iostream>

typedef glm::vec3 Vertex_Type;
typedef glm::vec2 UV_Type;
typedef glm::ivec3 Face_Type;
typedef glm::vec3 Normal_Type;

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
    std::vector<Vertex_Type> vertices;
    std::vector<UV_Type> uvs;
    std::vector<Face_Type> faces;
    std::vector<Normal_Type> normals;
public:
    /**
     * @brief
     * read Model File
     *
     * @param filePath
     */
    void readModel(const std::string &filePath) override
    {
        std::ifstream fin;
        fin.open(filePath);
        if(fin.fail())
        {
            std::cout<< "read model file fail !!\n";
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
                for(int i=0;i<3;i++)fin>>iparam[i];
                faces.emplace_back(iparam[0],iparam[1],iparam[2]);
            }
            else if ( type == "vt")
            {
                for(int i=0;i<2;i++)fin>>fparam[i];
                uvs.emplace_back(fparam[0],fparam[1]);
            }
        }
    }
};

