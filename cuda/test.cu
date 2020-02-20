#include <math.h>
#include <iostream>
#include <chrono>

// CUDA kernel to add elements of two arrays
__global__
void add(int n, float *x, float *y)
{
	for (int i = 0; i < n; i++)
		for (int a = 0; a < 666; a++)
			y[i] = std::sqrt(x[i]);
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

	int N = 1 << 16;
	float *x, *y;

	cudaMallocManaged(&x, N*sizeof(float));
	cudaMallocManaged(&y, N*sizeof(float));

	for (int i = 0; i < N; i++) {
		x[i] = 908397534.0f;
		y[i] = 0.0f;
	}

	time();

	add<<<1, 1>>>(N, x, y);

	cudaDeviceSynchronize();

	for (int i = 0; i < N; i++)
		std::cout << y[i] << std::endl;

	time();

	cudaFree(x);
	cudaFree(y);
}
