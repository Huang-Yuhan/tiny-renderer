#include "IShader.h"
#include "tgaimage.h"
#include "IModel.h"
#include <memory>
#include "ICamera.h"

namespace IRender
{

    /**
     * @brief
     * TinyRenderer的抽象类
     */
    class IRender
    {
        private:
        int width,height;
        std::shared_ptr<IShader::IShader> shader;
        std::shared_ptr<ICamera::ICamera> camera;
        std::shared_ptr<IModel::IModel> model;
        std::string filePath;
        public:
        void setModel(std::shared_ptr<IModel::IModel> _model)
        {
            model = _model;
        }
        void setShader(std::shared_ptr<IShader::IShader> _shader)
        {
            shader = _shader;
        }
        void setCamera(std::shared_ptr<ICamera::ICamera> _camera)
        {
            camera = _camera;
        }
        void setfilePath(const std::string &_filePath)
        {
            filePath=_filePath;
        }
        virtual void render()=0;
    };

}