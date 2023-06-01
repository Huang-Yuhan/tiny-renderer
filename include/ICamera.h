#include<glm/vec3.hpp>
#include<glm/matrix.hpp>

namespace ICamera
{
    typedef glm::mat4 mat;
    typedef glm::vec3 Position_Type;
    typedef glm::vec3 Direction_Type;

    /**
     * @brief
     * Camera的抽象类
     */
    class ICamera
    {
        private:
        Position_Type cameraPosition;
        Direction_Type cameraDirection;
        Direction_Type cameraRight;
        Direction_Type cameraUp;
        public:
        virtual mat GetLookAt()=0;
        void setCameraPosition(Position_Type cameraPosition)
        {
            this->cameraPosition=cameraPosition;
        }
        Position_Type getCameraPosition()const
        {
            return this->cameraPosition;
        }
    };

}