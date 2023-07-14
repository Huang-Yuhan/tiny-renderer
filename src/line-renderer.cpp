#include "../include/LineRenderer.h"
#include<iostream>
int main(int argc,char *argv[])
{
    /*if(argc!=2)
    {
        std::cout<<"<usage>: \n"<<argv[0]<<" <model file path>"<<std::endl;
        exit(0);
    }*/
    std::string s = "../../assets/floor.obj";
    //LineRenderer renderer(500,500,std::string(argv[1]));
    LineRenderer renderer(500,500,s);
    renderer.init();
    renderer.render();
    renderer.TestInfo();
    return 0;
}