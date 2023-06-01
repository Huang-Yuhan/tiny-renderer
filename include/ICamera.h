#include<glm/vec3.hpp>
#include<glm/matrix.hpp>

typedef glm::mat4 mat;

/**
 * @brief
 * Camera的抽象类
 */
class ICamera
{
    public:
    virtual mat GetLookAt()=0;
};