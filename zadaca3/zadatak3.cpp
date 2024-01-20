#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "tgaimage.h"
#include "tgaimage.cpp"
using namespace std;

const int width  = 512;
const int height = 512;


const TGAColor green = TGAColor(0, 255, 0, 1);
const TGAColor red   = TGAColor(255, 0, 0, 1);
const TGAColor blue  = TGAColor(0, 0, 255, 1);
const TGAColor cyan = TGAColor(0, 255, 255,1);              



void set_color(int x, int y, TGAImage &image, TGAColor color, bool invert = false)
{
    image.set(y, x, color);
}

float barycentric(float xa,float ya,float xc,float yc,float x,float y) 
{
    return ((ya - yc) * x + ( xc - xa ) * y + xa * yc - xc * ya);
}



void draw_triangle(TGAImage& image, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, TGAColor color) {

    x0 /= z0;
    y0 /= z0;
    x1 /= z1;
    y1 /= z1;
    x2 /= z2;
    y2 /= z2;

    x0 = (1 + x0) * 0.5 * width;
    x1 = (1 + x1) * 0.5 * width;
    x2 = (1 + x2) * 0.5 * width;

    y0 = (1 + y0) * 0.5 * height;
    y1 = (1 + y1) * 0.5 * height;
    y2 = (1 + y2) * 0.5 * height;

    float xmin = min(min(floor(x0), floor(x1)), floor(x2));
    float xmax = max(max(ceil(x0), ceil(x1)), ceil(x2));

    float ymin = min(min(floor(y0), floor(y1)), floor(y2));
    float ymax = max(max(ceil(y0), ceil(y1)), ceil(y2));

    for (float i = ymin; i <= ymax; ++i) {
        for (float j = xmin; j <= xmax; ++j) {
            float alpha = barycentric(x1, y1, x2, y2, j, i) / barycentric(x1, y1, x2, y2, x0, y0);
            float beta = barycentric(x2, y2, x0, y0, j, i) / barycentric(x2, y2, x0, y0, x1, y1);
            float gamma = barycentric(x0, y0, x1, y1, j,i) / barycentric(x0, y0, x1, y1, x2, y2);

            if (alpha > 0 && alpha < 1 && beta > 0 && beta < 1 && gamma > 0 && gamma < 1) {
                set_color(j, i, image, color);
            }
        }
    }
}

int main()
{
    
    TGAImage image(width, height, TGAImage::RGB);
    
   
    draw_triangle(image, -48, -10, 82, 29, -15, 44, 13, 34, 114, blue);

    
   	image.flip_vertically(); 
    image.write_tga_file("zadatak3.tga");
}