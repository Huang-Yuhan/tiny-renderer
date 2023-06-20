#include "IShader.h"
#include "tgaimage.h"
#include "IModel.h"
#include <memory>
#include "ICamera.h"

namespace IRenderSpace
{

    /**
     * @brief
     * TinyRenderer的抽象类
     */
    class IRender
    {
        private:
        int width,height;
        std::shared_ptr<IShaderSpace::IShader> shader;
        std::shared_ptr<ICameraSpace::ICamera> camera;
        std::shared_ptr<IModelSpace::IModel> model;
        std::string filePath;
        public:
        void setModel(std::shared_ptr<IModelSpace::IModel> _model)
        {
            model = _model;
        }
        void setShader(std::shared_ptr<IShaderSpace::IShader> _shader)
        {
            shader = _shader;
        }
        void setCamera(std::shared_ptr<ICameraSpace::ICamera> _camera)
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