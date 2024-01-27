#ifndef RAYTRACER_FACE_H
#define RAYTRACER_FACE_H

#include "vec3.h"
#include "point2.h"

class Face {
public:
    point3 v0;
    point3 v1;
    point3 v2;
    point2 vt0;
    point2 vt1;
    point2 vt2;
    vec3 vn0;
    vec3 vn1;
    vec3 vn2;
    Face(const point3& v0, const point3& v1, const point3& v2, const point2& vt0, const point2& vt1, const point2& vt2, const vec3& vn0, const vec3& vn1, const vec3& vn2) : v0{v0}, v1{v1}, v2{v2}, vt0{vt0}, vt1{vt1}, vt2{vt2}, vn0{vn0}, vn1{vn1}, vn2{vn2} {}

    vec3 interpolateNormal(double u, double v, double w) const {
        return unit_vector(vn0 * w + vn1 * u + vn2 * v);
    }
    point2 interpolateTexel(double u, double v, double w) const {
        return (vt0 * w + vt1 * u + vt2 * v);
    }
};

#endif //RAYTRACER_FACE_H
