#ifndef RAYTRACER_PARALLELLIGHT_H
#define RAYTRACER_PARALLELLIGHT_H

#include "Light.h"
#include "vec3.h"
#include "Ray.h"

class ParallelLight : public Light {
    const vec3 direction;
public:
    ParallelLight(const Color& color, const vec3& direction) : Light{color}, direction{unit_vector(direction)} {}

    double lambertian(const Intersection& intersection) const override { return std::max(dot(intersection.getNormal(), -direction), 0.0); }
    vec3 reflection(const Intersection& intersection) const override { return reflect(direction, intersection.getNormal()); }
    Ray castRayToLight(const Intersection& intersection) const override { return {intersection.getPosition(), -direction}; }
};

#endif //RAYTRACER_PARALLELLIGHT_H
