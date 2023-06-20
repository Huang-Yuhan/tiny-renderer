#include "ICamera.h"
/**
 * @brief 
 * 一个简单的摄像机类，实现了ICamera接口
 * 
 */
class SimpleCamera:public ICameraSpace::ICamera
{
private:
public:
    /**
     * @brief Get the Look At object
     * 
     * @return mat LooktAt矩阵
     */ 
    ICameraSpace::mat GetLookAt() override
    {
        ICameraSpace::mat leftMat=ICameraSpace::mat(1.0f);
        ICameraSpace::mat rightMat=ICameraSpace::mat(1.0f);

        /*glm mat是列主序的!!!*/

        /*构造rightMat*/
        rightMat[3][0]=-this->getCameraPosition().x;
        rightMat[3][1]=-this->getCameraPosition().y;
        rightMat[3][2]=-this->getCameraPosition().z;

        /*构造leftMat*/
        leftMat[0][0]=this->getCameraRight().x;
        leftMat[1][0]=this->getCameraRight().y;
        leftMat[2][0]=this->getCameraRight().z;
        leftMat[0][1]=this->getCameraUp().x;
        leftMat[1][1]=this->getCameraUp().y;
        leftMat[2][1]=this->getCameraUp().z;
        leftMat[0][2]=this->getCameraDirection().x;
        leftMat[1][2]=this->getCameraDirection().y;
        leftMat[2][2]=this->getCameraDirection().z;

        return leftMat*rightMat;
    }
};