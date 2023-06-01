#include "ICamera.h"
#include "IShader.h"
#include "tgaimage.h"
#include "IModel.h"
#include <memory>

/**
 * @brief
 * TinyRenderer的抽象类
 */
class IRender
{
    private:
    int width,height;
    std::shared_ptr<IShader> shader;
    std::shared_ptr<ICamera> camera;
    std::shared_ptr<IModel> model;
    std::string filePath;
    public:
    void setModel(std::shared_ptr<IModel> _model)
    {
        model = _model;
    }
    void setShader(std::shared_ptr<IShader> _shader)
    {
        shader = _shader;
    }
    void setCamera(std::shared_ptr<ICamera> _camera)
    {
        camera = _camera;
    }
    void filePath(const std::string &_filePath)
    {
        filePath=_filePath;
    }
    virtual void render()=0;
};