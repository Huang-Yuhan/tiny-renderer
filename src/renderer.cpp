#include "../include/Renderer.h"
#include "../include/RendererShader.h"

int main()
{
    std::string s;
    s = "../../assets/african_head/african_head.obj";
    //s = "../../assets/floor.obj";
    Renderer renderer(1500,1000,s);
    renderer.setShader(std::make_shared<RendererShader>());
    renderer.render();
    return 0;
}