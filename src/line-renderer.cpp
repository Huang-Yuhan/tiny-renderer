#include "../include/LineRenderer.h"
#include<iostream>
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        std::cout<<"<usage>: \n"<<argv[0]<<" <model file path>"<<std::endl;
        exit(0);
    }
    std::string s;
    s = argv[1];
    //s = "../../assets/floor.obj";
    LineRenderer renderer(500,500,s);
    renderer.init();
    std::cout<<"init finished"<<std::endl;
    std::cout<<"ready to render"<<std::endl;
    renderer.render();
    return 0;
}