#include<string>

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
        virtual std::vector<Vertex_Type>& getVertices()=0;
        virtual std::vector<UV_Type>& getUVs()=0;
        virtual std::vector<Face_Type>& getFaces()=0;
        virtual std::vector<Normal_Type>& getNormals()=0;
    };
}
