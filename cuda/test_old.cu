#include <math.h>
#include <iostream>
#include <chrono>

// CUDA kernel to add elements of two arrays
__global__
void add(int n, float *x, float *y)
{
	printf("- ");
	y[n] = std::sqrt(x[n]);
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

	add<<<5, 256>>>(N, x, y);

	cudaDeviceSynchronize();

	cudaFree(x);
	cudaFree(y);
}
