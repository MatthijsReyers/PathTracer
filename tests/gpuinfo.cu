
int main(int argc, char const *argv[])
{
    int count;
    cudaDeviceProp props;

    cudaGetDeviceCount(&count);

    for (int i = 0; i < count; i++)
    {
        cudaGetDeviceProperties(&props, i);
        std::cout << "Device name:           " << props.name << std::endl;
        std::cout << "Clock rate:            " << props.clockRate << std::endl;
        std::cout << "Max Threads Per Block: " << props.maxThreadsPerBlock << std::endl;
        std::cout << "Max Threads Dim:       " << props.maxThreadsDim[0] << ", " << props.maxThreadsDim[1] << ", " << props.maxThreadsDim[2] << std::endl;
        std::cout << "Max Grid Size:         " << props.maxGridSize[0] << ", " << props.maxGridSize[1] << ", " << props.maxGridSize[2] << std::endl;
    }
}
