#include<string>
#pragma once

namespace IModelSpace
{

    /**
     * @brief
     * 读取模型文件的抽象类
     */
    typedef glm::vec3 Vertex_Type;
    typedef glm::vec2 UV_Type;
    typedef std::tuple<glm::ivec3,glm::ivec3,glm::ivec3> Face_Type;
    typedef glm::vec3 Normal_Type;
    class IModel
    {
    private:
    public:
        TGAImage diffusemap{};         // diffuse color texture
        TGAImage normalmap{};          // normal map texture
        TGAImage specularmap{};        // specular map texture
        /**
         * @brief
         * 按照顺序依次为：
         * 顶点坐标
         * 贴图坐标
         * 面
         * 法向量
         */
        std::vector<Vertex_Type> vertices;
        std::vector<UV_Type> uvs;
        std::vector<Face_Type> faces;
        std::vector<Normal_Type> normals;
        virtual void readModel(const std::string &filePath)=0;
        std::vector<Vertex_Type>& getVertices()
        {
            return vertices;
        }
        std::vector<UV_Type>& getUVs()
        {
            return uvs;
        }
        std::vector<Face_Type>& getFaces()
        {
            return faces;
        }
        std::vector<Normal_Type>& getNormals()
        {
            return normals;
        }
        Normal_Type getNormalFromFile(glm::vec2 uv)
        {
            TGAColor c = normalmap.get(uv.x*normalmap.width(), uv.y*normalmap.height());
            return Normal_Type(c[0]*2.f/255.f-1., c[1]*2.f/255.f-1., c[2]*2.f/255.f-1.);
        }
        static TGAColor sample2D(const TGAImage &img, glm::vec2 uv) 
        {
            return img.get(uv.x*img.width(), uv.y*img.height());
        }
    };
}
