#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "tgaimage.h"
#include "tgaimage.cpp"
using namespace std;

const int width = 512;
const int height = 512;

const TGAColor cyan = TGAColor(0, 255, 255, 1);
const TGAColor red = TGAColor(255, 0, 0, 1);

float barycentric(float x0, float y0, float x1, float y1, float x2, float y2, float x, float y)
{
    return ((y1 - y2) * (x - x2) + (x2 - x1) * (y - y2)) /
           ((y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2));
}

void draw_triangle_2d(float x0, float y0, float x1, float y1, float x2, float y2, TGAImage &image, TGAColor color)
{
    int maxX = ceil(max(max(x0, x1), x2));
    int minX = floor(min(min(x0, x1), x2));

    int maxY = ceil(max(max(y0, y1), y2));
    int minY = floor(min(min(y0, y1), y2));

    float alpha, beta, gamma;

    for (int j = minY; j <= maxY; ++j)
    {
        for (int i = minX; i <= maxX; ++i)
        {
            alpha = barycentric(x1, y1, x2, y2, x0, y0, i, j);
            beta = barycentric(x2, y2, x0, y0, x1, y1, i, j);
            gamma = barycentric(x0, y0, x1, y1, x2, y2, i, j);

            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {
                image.set(i, j, color);
            }
        }
    }
}

int main()
{

    TGAImage image(width, height, TGAImage::RGB);

    draw_triangle_2d(20, 40, 180, 160, 120, 240, image, cyan);
    draw_triangle_2d(200, 200, 300, 250, 200, 340, image, red);

    image.flip_vertically();
    image.write_tga_file("zadatak1.tga");
}