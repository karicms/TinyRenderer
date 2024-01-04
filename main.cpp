#include<stdio.h>
#include<iostream>
#include"tgaimage.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);//白色
const TGAColor red = TGAColor(255, 0, 0, 255);//红色
    void line(int x0, int y0, int x1, int y1, TGAImage & image, const TGAColor & color)
    {
        bool steep = false;
        if (std::abs(x0 - x1) < std::abs(y0 - y1))
        {
            std::swap(x0, y0);
            std::swap(x1, y1);
            steep = true;
        }
        if (x0 > x1) {      
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        int dx = x1 - x0;
        int dy = y1 - y0;
        int derror2 = std::abs(dy) * 2;
        int error2 = 0;
        int y = y0;
        for (int x = x0; x <= x1; x++) {
            if (steep) {
                image.set(y, x, color);
            }
            else {
                image.set(x, y, color);
            }
            error2 += derror2;
            if (error2 > dx) {
                y += (y1 > y0 ? 1 : -1);
                error2 -= dx * 2;
            }
        }
    }
    void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, const TGAColor& color)
    {
        line(t0.x, t0.y, t1.x, t1.y, image, color);
        line(t1.x, t1.y, t2.x, t2.y, image, color);
        line(t2.x, t2.y, t0.x, t0.y, image, color);
    }

 int main(int argc, char** argv) 
 {

        TGAImage image(100, 100, TGAImage::RGB);//100*100的图像，每像素三个字节存储RGB值
       // image.set(52, 41, red);//把（52，41）位置的像素设置为红色
        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        Vec2i t0[3]= { Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80) };
        image.write_tga_file("output.tga");//写出图像
        return 0;
 }
