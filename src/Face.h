#ifndef RAYTRACER_FACE_H
#define RAYTRACER_FACE_H

#include "vec3.h"

class Face {
public:
    point3 v0;
    point3 v1;
    point3 v2;
    vec3 vn0;
    vec3 vn1;
    vec3 vn2;
    Face(const point3& v0, const point3& v1, const point3& v2, const vec3& vn0, const vec3& vn1, const vec3& vn2) : v0{v0}, v1{v1}, v2{v2}, vn0{vn0}, vn1{vn1}, vn2{vn2} {}
};

#endif //RAYTRACER_FACE_H
