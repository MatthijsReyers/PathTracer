#include <iostream>
#include <fstream>
#include <cstdlib>

#include "vec3.h"
// #include "ray.h"
// #include "sphere.h"
// #include "hittable.h"
// #include "hitable_list.h"
// #include "camera.h"
// #include "image.h"

#define WIDTH 600
#define HEIGHT 400
#define SAMPLES 50
#define CAMERA_DISTANCE -1
#define RENDERPLANE_SCALE 4

__global__
void renderPixel(int n, vec3 *pixels)
{
	pixels[n] = vec3(1.0, 0, 0);
}

int main(int argv, char** argc)
{
	vec3 *pixels;
	cudaMallocManaged(&pixels, WIDTH*HEIGHT*sizeof(vec3));

	renderPixel<<<1, 1>>>( int(WIDTH*HEIGHT), pixels);

	cudaDeviceSynchronize();

	std::ofstream file;
	file.open("out.ppm");
	file << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

    for (int i = WIDTH*HEIGHT; i > 0; i--)
    {
        vec3 pixel = pixels[i];

        int red = int(255.99 * pixel.r());
        int green = int(255.99 * pixel.g());
        int blue = int(255.99 * pixel.b());

        file << red << " " << green << " " << blue << "\n";
    }

    file.close();
}
