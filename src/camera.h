#pragma once

#include "ray.h"
#include "vec3.h"

class camera
{
    // private:
    //     int width, height, RENDERPLANE_SCALE;

    public:
        camera(int width, int height, int CAMERA_DISTANCE, int RENDERPLANE_SCALE);

        __host__ __device__
        ray get_ray(float u, float v);

        vec3 origin, horizontal, vertical, bottomLeft;
};

camera::camera(int width, int height, int CAMERA_DISTANCE, int RENDERPLANE_SCALE)
{
    float renderPlaneHeight = (float(height)/float(width)) * float(RENDERPLANE_SCALE);
	float renderPlaneWidth = 1.0 * float(RENDERPLANE_SCALE);

	vec3 origin = vec3(0.0, 0.0, 0.0);
	vec3 horizonal = vec3(renderPlaneWidth, 0.0, 0.0);
	vec3 vertical = vec3(0.0, renderPlaneHeight, 0.0);
	vec3 bottomLeft = vec3(renderPlaneWidth / -2.0, renderPlaneHeight / -2.0, float(CAMERA_DISTANCE));
}

__host__ __device__
ray camera::get_ray(float u, float v)
{
    return ray(origin, bottomLeft + u*horizontal + v*vertical - origin);
}