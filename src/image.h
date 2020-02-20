#pragma once

#include <fstream>

#include "vec3.h"

class image
{
    private:
        int width;
        int height;
        vec3 *pixels;

    public:
        image(int w, int h);

        void close();
        __host__ __device__
        void setPixel(int w, int h, float r, float g, float b);
        __host__ __device__
        void setPixel(int n, float r, float g, float b);
        void write(const char* url);
};

image::image(int w, int h)
{
    width = w;
    height = h;

    cudaMallocManaged(&pixels, w*h*sizeof(vec3));
}

void image::close()
{
    cudaFree(pixels);
}

void image::setPixel(int w, int h, float r, float g, float b)
{
    pixels[h*width + w] = vec3(r,g,b);
}

__host__ __device__
void image::setPixel(int n, float r, float g, float b)
{
    pixels[n] = vec3(r,g,b);
}

void image::write(const char* url)
{
	std::ofstream file;
	file.open(url);
	file << "P3\n" << width << " " << height << "\n255\n";

    for (int i = width*height; i > 0; i--)
    {
        vec3 pixel = pixels[i];

        int red = int(255.99 * pixel.r());
        int green = int(255.99 * pixel.g());
        int blue = int(255.99 * pixel.b());

        file << red << " " << green << " " << blue << "\n";
    }

    file.close();
}
