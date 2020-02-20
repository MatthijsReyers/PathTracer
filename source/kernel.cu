
__global__
void render()
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    printf(index);
}