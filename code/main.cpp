#include <iostream>
#include <fstream>

#include "vec3.h"

int main(int argv, char** argc)
{
    const char* OutFileName = "out.ppm";
    std::ofstream OutFile;
    OutFile.open(OutFileName);

    int nx = 400;
    int ny = 400;
    OutFile << "P3\n" << nx << " " << ny << "\n255\n";

    for (int h = ny-1; h >= 0; h--)
    {
        for (int w = 0; w < nx; w++)
        {
            vec3 col(
                float(h) / float(ny), 
                float(w) / float(ny), 
                float(w) / float(ny)
            );

            int ir = int(255.99 * col.r);
            int ig = int(255.99 * col.g);
            int ib = int(255.99 * col.b);

            OutFile << ir << " " << ig << " " << ib << "\n";
        }
    }

    OutFile.close();
}

