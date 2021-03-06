#pragma once

#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class sphere: public hittable
{
    public:
        sphere() {}
        sphere(vec3 cen, float r) : center(cen), radius(r)  {};

        __host__ __device__
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        
        vec3 center;
        float radius;
};

__host__ __device__
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const 
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}
