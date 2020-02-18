#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"

#define HEIGHT 400
#define WIDTH 800
#define CAMERA_DISTANCE -1
#define RENDERPLANE_SCALE 2

vec3 colorSky(const ray& r)
{
	vec3 unitDirection = unit_vector(r.direction());
	float t = 0.5 * (unitDirection.y() + 1.0);
	return (1.0-t) * vec3(1.0,1.0,1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(int argv, char** argc)
{
	const char* OutFileName = "out.ppm";
	std::ofstream OutFile;
	OutFile.open(OutFileName);
	OutFile << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

	float renderPlaneHeight = (float(HEIGHT)/float(WIDTH)) * float(RENDERPLANE_SCALE);
	float renderPlaneWidth = 1.0 * float(RENDERPLANE_SCALE);

	std::cout << "renderPlaneWidth: " << renderPlaneWidth << std::endl;
	std::cout << "renderPlaneHeight: " << renderPlaneHeight << std::endl;

	vec3 origin = 		vec3(0.0, 0.0, 0.0);
	vec3 horizonal = 	vec3(renderPlaneWidth, 0.0, 0.0);
	vec3 vertical = 	vec3(0.0, renderPlaneHeight, 0.0);
	vec3 bottomLeft = 	vec3(renderPlaneWidth / -2.0, renderPlaneHeight / -2.0, float(CAMERA_DISTANCE));

	sphere s1(vec3(0,0,-2), 0.5);
	vec3 colour;

	for (int h = HEIGHT; h > 0; h--)
	{
		for (int w = 0; w < WIDTH; w++)
		{
			float u = float(w) / float(WIDTH);
			float v = float(h) / float(HEIGHT);

			ray r(origin, bottomLeft + u*horizonal + v*vertical);

			if (s1.hit(r)) colour = vec3(1.0, 0, 0);
			else colour = colorSky(r);

			int ir = int(255.99 * colour.r());
			int ig = int(255.99 * colour.g());
			int ib = int(255.99 * colour.b());

			OutFile << ir << " " << ig << " " << ib << "\n";
		}
	}

	OutFile.close();
}

