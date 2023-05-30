#include<tgaimage.h>
#include<iostream>

const TGAColor white=TGAColor(255,255,255,255);
constexpr int width=500;
constexpr int height=500;

void line_draw(int x0,int y0,int x1,int y1,TGAImage &img,TGAColor color)
{
    
    std::cout<<"writing a line from ("<<x0<<","<<y0<<") to ("<<x1<<","<<y1<<")"<<std::endl;

    //double t belongs to [0,1]
    int dx,dy;
    dx=x1-x0;
    dy=y1-y0;
    if(std::abs(dx)>std::abs(dy))
    {
        double xincr=1.0*dx/std::abs(dx);
        double yincr=1.0*dy/std::abs(dx);
        double x=x0,y=y0;
        for(int t=std::abs(dx);t>0;t--)
        {
            img.set(x,y,color);
            x+=xincr;
            y+=yincr;
            std::cout<<"("<<x<<","<<y<<")"<<std::endl;
        }
    }
    else
    {
        double xincr=dx/std::abs(dy);
        double yincr=dy/std::abs(dy);
        double x=x0,y=y0;
        for(int t=std::abs(dy);t>0;t--)
        {
            img.set(x,y,color);
            x+=xincr;
            y+=yincr;
            std::cout<<"("<<x<<","<<y<<")"<<std::endl;
        }
    }
}

int main(int argc,char *argv[])
{
    if(argc !=5 && argc != 6)
    {
        std::cout<<"<usage>: \n"<<argv[0]<<" x0 y0 x1 y1"<<std::endl;

        std::cout<<"this program is just draw a line from(x0,y0) to (x1,y1)\nthe output file is output.tga\n";

        exit(0);
    }

    int x0=atoi(argv[1]);
    int y0=atoi(argv[2]);
    int x1=atoi(argv[3]);
    int y1=atoi(argv[4]);

    TGAImage img(width,height,TGAImage::RGB);

    line_draw(x0,y0,x1,y1,img,white);

    img.flip_vertically();
    img.write_tga_file("output.tga");

    return 0;
}