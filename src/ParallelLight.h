#ifndef RAYTRACER_PARALLELLIGHT_H
#define RAYTRACER_PARALLELLIGHT_H

#include "Light.h"
#include "vec3.h"
#include "Ray.h"

class ParallelLight : public Light {
    const vec3 direction;
public:
    ParallelLight(const Color& color, const vec3& direction) : Light{color}, direction{unit_vector(direction)} {}

    double lambertian(const vec3& normal) const override { return std::max(dot(normal, -direction), 0.0); }
    vec3 reflection(const vec3& normal) const override { return reflect(direction, normal); }
    Ray castRayToLight(const point3& origin) const override { return {origin, -direction}; }
};

#endif //RAYTRACER_PARALLELLIGHT_H
