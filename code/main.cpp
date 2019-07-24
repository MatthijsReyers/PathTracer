#include <iostream>
#include <fstream>

#include <math.h>
#include <stdlib.h>

int main(int argv, char** argc)
{
    const char* OutFileName = "/images/out.ppm";
    std::ofstream OutFile;
    OutFile.open(OutFileName);

    int nx = 400;
    int ny = 400;
    OutFile << "P3\n" << nx << " " << ny << "\n255\n";

    for (int h = ny-1; h >= 0; h--)
    {
        for (int w = 0; w < nx; w++)
        {
            float r = float(h) / float(ny);
            float g = float(h) / float(ny);
            float b = float(h) / float(ny);

            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);

            OutFile << ir << " " << ig << " " << ib << "\n";
        }
    }

    OutFile.close();
}

