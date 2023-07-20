#include<glm/vec3.hpp>
#include<glm/matrix.hpp>
#pragma once

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
        Position_Type cameraTarget;
        Direction_Type globalUpDirection=Direction_Type(0.0f,1.0f,0.0f);
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
        void setCameraTarget(Position_Type cameraTarget)
        {
            this->cameraTarget=cameraTarget;
        }
        Direction_Type getGlobalUpDirection()const
        {
            return this->globalUpDirection;
        }
        void initVector()
        {
            this->cameraDirection=glm::normalize(this->cameraPosition-this->cameraTarget);
            this->cameraRight=glm::normalize(glm::cross(this->globalUpDirection,this->cameraDirection));
            this->cameraUp=glm::normalize(glm::cross(this->cameraDirection,this->cameraRight));
        }
        Direction_Type getCameraDirection()const
        {
            return this->cameraDirection;
        }
        Direction_Type getCameraRight()const
        {
            return this->cameraRight;
        }
        Direction_Type getCameraUp()const
        {
            return this->cameraUp;
        }
    };

}