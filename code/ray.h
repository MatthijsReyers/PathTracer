#ifndef RAYH
#define RAYH


#include "vec3.h"

class ray
{
    public:
        // Two vectors for keeping track of the ray's origin and direction in the world space.
        // --------------------------------------------------------------------------------
        vec3 A;
        vec3 B;

        // 
        // --------------------------------------------------------------------------------
        ray() {};
        ray(const vec3& vecA, const vec3& vecB) {A = vecA; B = vecB;}

        // 
        // --------------------------------------------------------------------------------
        vec3 origin() const {return A;}
        vec3 direction() const {return B;}
        vec3 point_at_parameter(float t) const {return A + t*B;}

};

#endif