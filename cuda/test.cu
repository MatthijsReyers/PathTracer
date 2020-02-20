#include <math.h>
#include <iostream>
#include <fstream>
#include <chrono>

#define DIMENSION 512

// CUDA kernel to add elements of two arrays
__global__
void render(int n, float *x, float *y, float *pixels)
{
	x[n] = 500.0;
	// pixels[n*3+0] = 0.0;
	// pixels[n*3+1] = 0.5;
	// pixels[n*3+2] = 1.0;
}

void time()
{
	int now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << now << std::endl;
}

int main(void)
{
	cudaError_t error  = cudaGetLastError();
	if (error != 0) {
		std::cout << "ERROR: could not start program CUDA gave error: " << cudaGetErrorString(error) << std::endl;
		return 1;
	}

	int N = 1 << 18;
	float *x, *y, *pixels;

	cudaMallocManaged(&x, N*sizeof(float));
	cudaMallocManaged(&y, N*sizeof(float));
	cudaMallocManaged(&pixels, 3*N*sizeof(float));

	error  = cudaGetLastError();
	if (error != 0) {
		std::cout << "ERROR: this happened: " << cudaGetErrorString(error) << std::endl;
		return 1;
	}

	for (int i = 0; i < N; i++) {
		x[i] = 2.0f;
		y[i] = 1.0f;
		pixels[i] = 0.0f;
	}

	time();

	render<<<1, 1>>>(N, x, y, pixels);

	cudaDeviceSynchronize();

	time();

	error  = cudaGetLastError();
	if (error != 0) {
		std::cout << "ERROR: this happened: " << cudaGetErrorString(error) << std::endl;
		return 1;
	}

	for (int i = 0; i < N; i++) {
		std::cout << x[i] << " " << y[i] << std::endl;
	}

	// std::ofstream file;
	// file.open("out.ppm");
	// file << "P3\n" << DIMENSION << " " << DIMENSION << "\n255\n";
	// std::cout << "writing file\n";
    // for (int i = DIMENSION*DIMENSION -1; i > 0; i--)
    // {
    //     int red = int(255.99 * pixels[i*3+0]);
    //     int green = int(255.99 * pixels[i*3+1]);
    //     int blue = int(255.99 * pixels[i*3+2]);

    //     file << red << " " << green << " " << blue << "\n";
    // }
	// file.close();
	
	cudaFree(x);
	cudaFree(y);
	cudaFree(pixels);
}
