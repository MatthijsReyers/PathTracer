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
        void setPixel(int w, int h, float r, float g, float b);
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
    pixels[w + (h*(w+1))] = vec3(r,g,b);
}

void image::write(const char* url)
{
	std::ofstream file;
	file.open(url);
	file << "P3\n" << width << " " << height << "\n255\n";

	for (int h = height-1; h >= 0; h--) {
		for (int w = 0; w < width; w++) {

            vec3 pixel = pixels[w + (h*(w+1))];

            int red = int(255.99 * pixel.r());
            int green = int(255.99 * pixel.g());
            int blue = int(255.99 * pixel.b());

            file << red << " " << green << " " << blue << "\n";
        }
    }

    file.close();
}
