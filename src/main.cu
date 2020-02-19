#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "image.h"

#define WIDTH 800
#define HEIGHT 400
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
	std::cout << sizeof(vec3) << std::endl;
	std::cout << sizeof(float) << std::endl;

	image output(WIDTH, HEIGHT);

	float renderPlaneHeight = (float(HEIGHT)/float(WIDTH)) * float(RENDERPLANE_SCALE);
	float renderPlaneWidth = 1.0 * float(RENDERPLANE_SCALE);

	vec3 origin = 		vec3(0.0, 0.0, 0.0);
	vec3 horizonal = 	vec3(renderPlaneWidth, 0.0, 0.0);
	vec3 vertical = 	vec3(0.0, renderPlaneHeight, 0.0);
	vec3 bottomLeft = 	vec3(renderPlaneWidth / -2.0, renderPlaneHeight / -2.0, float(CAMERA_DISTANCE));

	sphere s1(vec3(0,0,-2), 0.5);
	vec3 x;

	for (int h = 0; h < HEIGHT; h++)
	{
		for (int w = 0; w < WIDTH; w++)
		{
			float u = float(w) / float(WIDTH);
			float v = float(h) / float(HEIGHT);

			ray r(origin, bottomLeft + u*horizonal + v*vertical);

			if (s1.hit(r)) x = vec3(1.0, 0, 0);
			else x = colorSky(r);


			float red = 0.0;
			if (w > WIDTH/2)
				red = 1.0;

			float green = 0.0;
			if (w == h)
				green = 1.0;

			float blue = u;

			output.setPixel(w, h, red, green, blue);
			// output.setPixel(w, h, x.r(),x.g(),x.b());
		}
	}

	output.write("out.ppm");
	output.close();
}

