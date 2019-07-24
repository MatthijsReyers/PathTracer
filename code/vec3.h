#ifndef VEC3H
#define VEC3H

// This one is not nessessary, I think? 
#include <stdlib.h>

// <math.h> is needed for the sqrt() function. <iostream> is nessessary to be able to 
// define the vec3 class's behaviour for the '<<' and '>>' operators.
// ----------------------------------------------------------------------------------------
#include <iostream>
#include <math.h>

class vec3 
{
    public:
        // Array of floats that contains the magnitudes of the vector.
        // --------------------------------------------------------------------------------
        float e[3];

        // 
        // --------------------------------------------------------------------------------
        vec3() {};
        vec3(float e0, float e1, float e2) {e[0] = e0; e[1] = e1; e[2] = e2;}

        // Defining X, Y, and Z. As well as R, G, and B. Because We'll use this vector 
        // class both for determining space as wel as colours.
        // --------------------------------------------------------------------------------
        inline float x() const {return e[0];}
        inline float y() const {return e[1];}
        inline float z() const {return e[2];}
        inline float r() const {return e[0];}
        inline float g() const {return e[1];}
        inline float b() const {return e[2];}

        // 
        // --------------------------------------------------------------------------------
        inline const vec3& operator+() const {return *this;}
        inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}

        // Array operator, one returns a float and one returns a pointer, I don't know why
        // there need to be two, but sure.
        // --------------------------------------------------------------------------------
        inline float operator[](int i) const {return e[i];}
        inline float& operator[](int i) {return e[i];};

        // Takes care of all the basic math operators when applying one vector to another.
        // --------------------------------------------------------------------------------
        inline vec3& operator+=(const vec3 &v2);
        inline vec3& operator-=(const vec3 &v2);
        inline vec3& operator*=(const vec3 &v2);
        inline vec3& operator/=(const vec3 &v2);

        // Takes care of all the basic math operators when applying a vector to a float.
        // --------------------------------------------------------------------------------
        inline vec3& operator*=(const float t);
        inline vec3& operator/=(const float t);

        // Calculates the length of the vector.
        // --------------------------------------------------------------------------------
        inline float length() const {return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}

        // Calculates the length of the vector, but without the heavy ass square root operation. 
        // --------------------------------------------------------------------------------
        inline float squared_length() const {return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}

        // Calculates the unit vector, see: https://en.wikipedia.org/wiki/Unit_vector.
        // --------------------------------------------------------------------------------
        inline void make_unit_vector()
        {
            float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
            e[0] *= k; e[1] *= k; e[2] *= k;
        }
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator/(vec3 v, float t) {
    return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline vec3 operator*(const vec3 &v, float t) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline float dot(const vec3 &v1, const vec3 &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}

inline vec3& vec3::operator+=(const vec3 &v){
    e[0]  += v.e[0];
    e[1]  += v.e[1];
    e[2]  += v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v){
    e[0]  *= v.e[0];
    e[1]  *= v.e[1];
    e[2]  *= v.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v){
    e[0]  /= v.e[0];
    e[1]  /= v.e[1];
    e[2]  /= v.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3& v) {
    e[0]  -= v.e[0];
    e[1]  -= v.e[1];
    e[2]  -= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const float t) {
    e[0]  *= t;
    e[1]  *= t;
    e[2]  *= t;
    return *this;
}

inline vec3& vec3::operator/=(const float t) {
    float k = 1.0/t;
    e[0]  *= k;
    e[1]  *= k;
    e[2]  *= k;
    return *this;
}

// See: https://en.wikipedia.org/wiki/Unit_vector when confused.
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif