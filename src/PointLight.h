#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

#include "Light.h"
#include "vec3.h"
#include "Ray.h"

class PointLight : public Light {
    const point3 position;
public:
    PointLight(const Color& color, const point3& position) : Light{color}, position{position} {}

    double lambertian(const Intersection& intersection) const override { return std::max(dot(intersection.getNormal(), unit_vector(position - intersection.getPosition())), 0.0); }
    vec3 reflection(const Intersection& intersection) const override { return reflect(unit_vector(intersection.getPosition() - position), intersection.getNormal()); }
    Ray castRayToLight(const Intersection& intersection) const override {
        vec3 v{position - intersection.getPosition()};
        Ray ray{intersection.getPosition(), unit_vector(v)};
        ray.setMaxDistance(v.length());
        return ray;
    }
};

#endif //RAYTRACER_POINTLIGHT_H
