#include<glm/vec3.hpp>
#include<glm/matrix.hpp>
#include"tgaimage.h"

namespace IShaderSpace
{

    typedef glm::vec3 Light_Type;
    typedef glm::vec3 Vertex_Type;

    /**
     * @brief
     * Shader的抽象类
     */
    class IShader
    {
        public:
        virtual Vertex_Type vertex_shader(Vertex_Type vertex)=0;
        virtual void fragment_shader(Light_Type light,TGAColor &color)=0;
    };

}