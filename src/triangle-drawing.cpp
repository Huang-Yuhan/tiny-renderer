#include<iostream>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<tgaimage.h>
#include<map>
#include<algorithm>

typedef glm::vec4 Triangle_Color;

class Triangle
{
    private:
    glm::vec2 vertices[3];
    Triangle_Color color[3];
    public:
    Triangle(glm::vec2 a,glm::vec2 b,glm::vec2 c,Triangle_Color aa,Triangle_Color bb,Triangle_Color cc)
    {
        vertices[0]=a;
        vertices[1]=b;
        vertices[2]=c;

        color[0]=aa;
        color[1]=bb;
        color[2]=cc;
    }

    glm::vec3 get_barycentric_coordinates(glm::vec2 vertex)
    {
        float alpha,beta,gamma;
        glm::vec2 &a=vertices[0],&b=vertices[1],&c=vertices[2];
        gamma = ((a.y-b.y)*vertex.x+(b.x-a.x)*vertex.y+a.x*b.y-b.x*a.y) / ((a.y-b.y)*c.x+(b.x-a.x)*c.y+a.x*b.y-b.x*a.y);
        beta = ((a.y-c.y)*vertex.x+(c.x-a.x)*vertex.y+a.x*c.y-c.x*a.y) / ((a.y-c.y)*b.x+(c.x-a.x)*b.y+a.x*c.y-c.x*a.y);
        alpha = 1 - beta - gamma;

        return glm::vec3(alpha,beta,gamma);
    }

    std::pair<glm::vec2,glm::vec2> get_bounding_box()
    {
        std::pair<glm::vec2,glm::vec2> ans;

        float xmin = vertices[0].x;
        float ymin = vertices[0].y;
        float xmax = xmin;
        float ymax = ymin;

        for(int i=1;i<3;i++)
        {
            xmin = std::min(xmin,vertices[i].x);
            xmax = std::max(xmax,vertices[i].x);
            ymin = std::min(ymin,vertices[i].y);
            ymax = std::max(ymax,vertices[0].y);
        }

        ans.first = glm::vec2(xmin,ymin);
        ans.second = glm::vec2(xmax,ymax);
        return ans;
    }
    Triangle_Color get_interpolation_color(glm::vec3 bary_cc)
    {
        Triangle_Color ans = bary_cc.x*color[0]+bary_cc.y*color[1]+bary_cc.z*color[2];
        return ans;
    }
};

void draw_triangle(Triangle &triangle,TGAImage &img)
{
    std::pair<glm::vec2,glm::vec2> bouding_box = triangle.get_bounding_box();

    for ( int x = bouding_box.first.x ; x <= bouding_box.second.x ; x++)
        for ( int y = bouding_box.first.y; y <= bouding_box.second.y; y++)
        {
            glm::vec3 bary_cc = triangle.get_barycentric_coordinates(glm::vec2(x,y));

            if(bary_cc.x<0||bary_cc.y<0||bary_cc.z<0)  // 不在三角形中
                continue;

            Triangle_Color color_vec = triangle.get_interpolation_color(bary_cc);

            TGAColor color = TGAColor(color_vec.x,color_vec.y,color_vec.z,color_vec.w);

            img.set(x,y,color);

        }
}

int main(int argc,char *argv[])
{
    TGAImage img(500,500,TGAImage::RGB);
    Triangle_Color white=glm::vec4(255,255,255,255);
    Triangle triangle(glm::vec2(400,400),glm::vec2(200,400),glm::vec2(300,100),white,white,white);

    draw_triangle(triangle,img);

    img.flip_vertically();

    img.write_tga_file("output.tga");

    return 0;
}