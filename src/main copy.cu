#include <iostream>
#include <cstdlib>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "hitable_list.h"
#include "camera.h"
#include "image.h"

#define WIDTH 600
#define HEIGHT 400
#define SAMPLES 50
#define CAMERA_DISTANCE -1
#define RENDERPLANE_SCALE 4


__host__ __device__
inline vec3 color(const ray& r, hittable *world)
{
    hit_record rec;

	if (world->hit(r, 0.0, MAXFLOAT, rec))
        return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);

	else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

__global__
void renderPixel(int n, hittable_list *world, camera cam, image output)
{
	int w = (n % WIDTH);
	int h = n / WIDTH;

	vec3 col(1, 0, 1);
	// for (int s = 0; s < SAMPLES; s++)
	// {
	// 	float u = float(w) + (float(s/SAMPLES) / float(WIDTH));
	// 	float v = float(h) + (float(s/SAMPLES) / float(HEIGHT));
	// 	ray r = cam.get_ray(u, v);
	// 	col += color(r, world);
	// }
	// col /= float(SAMPLES);

	output.setPixel(w, h, col.e[0], col.e[1], col.e[2]);
}

int main(int argv, char** argc)
{
	vec3 *pixels;
	cudaMallocManaged(&pixels, w*h*sizeof(vec3));

	renderPixel<<<1, 1>>>( int(WIDTH*HEIGHT), pixels);

	cudaDeviceSynchronize();

	// hittable *list[2];
    // list[0] = new sphere(vec3(0,0,-1), 0.5);
    // list[1] = new sphere(vec3(0,-100.5,-1), 100);
    // hittable_list *world = new hittable_list(list,2);

	// image output(WIDTH, HEIGHT);
	// camera cam(WIDTH, HEIGHT, CAMERA_DISTANCE, RENDERPLANE_SCALE);

	// for (int h = 0; h < HEIGHT; h++)
	// {
	// 	for (int w = 0; w < WIDTH; w++)
	// 	{
	// 		vec3 col(0, 0, 0);
	// 		for (int s = 0; s < SAMPLES; s++)
	// 		{
    //             float u = float(w + (rand() / (RAND_MAX + 1.0))) / float(WIDTH);
    //             float v = float(h + (rand() / (RAND_MAX + 1.0))) / float(HEIGHT);
    //             ray r = cam.get_ray(u, v);
    //             col += color(r, world);
    //         }
    //         col /= float(SAMPLES);
			
	// 		output.setPixel(w, h, col.r(), col.g(), col.b());
	// 	}
	// }

	// output.write("out.ppm");
	// output.close();
}
