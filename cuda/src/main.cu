#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <unistd.h>

#define WIDTH 600
#define HEIGHT 400

__global__
void renderPixel(int n, float *pixels)
{
	for (int i = 0; i < n; i++)
		for (int a = 0; a < 666; a++)
			std::sqrt(n);

	// pixels[n*3+0] = 1.0f;
	// pixels[n*3+1] = 0.0f;
	// pixels[n*3+2] = 1.0f;
}

int main(int argv, char** argc)
{
	float *pixels;

	std::cout << "Cuda error state: " << cudaGetLastError() << std::endl;
	std::cout << "Cuda error state: " << cudaGetLastError() << std::endl;

	cudaMallocManaged(&pixels, 3*WIDTH*HEIGHT*sizeof(float));

	std::cout << "Starting this many cuda cores: " << WIDTH*HEIGHT << std::endl;

	renderPixel<<<1, 1>>>(WIDTH*HEIGHT, pixels);

	std::cout << "Waiting for devices to sync..." << std::endl;

	usleep(100000);

	cudaDeviceSynchronize();

	std::cout << "Done!" << std::endl;

	std::ofstream file;
	file.open("out.ppm");
	file << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

    for (int i = WIDTH*HEIGHT; i > 0; i--)
    {
        int red = int(255.99 * pixels[i*3+0]);
        int green = int(255.99 * pixels[i*3+1]);
        int blue = int(255.99 * pixels[i*3+2]);

        file << red << " " << green << " " << blue << "\n";
        // std::cout << red << " " << green << " " << blue << "\n";
    }

	cudaFree(pixels);

    file.close();
}
