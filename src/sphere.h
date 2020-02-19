#pragma once

#include "vec3.h"
#include "ray.h"

class sphere
{
    private:
        // Center and radius of the sphere.
        // -------------------------------------------------------------------------------
        vec3 center;
        float radius;
        float radiusSquared;

    public:
        // Constructors.
        // --------------------------------------------------------------------------------
        sphere() {};
        sphere(vec3 c, float r) {center = c; radius = r; radiusSquared = r*r;}

        bool inline hit(const ray& r);
};

bool inline sphere::hit(const ray& r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radiusSquared;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}