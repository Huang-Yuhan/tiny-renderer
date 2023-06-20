#include<string>

namespace IModelSpace
{

    /**
     * @brief
     * 读取模型文件的抽象类
     */
    class IModel
    {
    private:
    public:
        virtual void readModel(const std::string &filePath)=0;
    };
}
