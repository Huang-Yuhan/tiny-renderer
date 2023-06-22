#include<glm/vec3.hpp>
#include<glm/matrix.hpp>

namespace ICameraSpace
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
        Direction_Type cameraDirection; //应该是实际direction的负数
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
        void setCameraDirection(Direction_Type cameraDirection)
        {
            this->cameraDirection=cameraDirection;
        }
        Direction_Type getCameraDirection()const
        {
            return this->cameraDirection;
        }
        void setCameraRight(Direction_Type cameraRight)
        {
            this->cameraRight=cameraRight;
        }
        Direction_Type getCameraRight()const
        {
            return this->cameraRight;
        }
        void setCameraUp(Direction_Type cameraUp)
        {
            this->cameraUp=cameraUp;
        }
        Direction_Type getCameraUp()const
        {
            return this->cameraUp;
        }
    };

}