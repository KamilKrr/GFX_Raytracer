#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H

#include "Light.h"

class AmbientLight : public Light {
public:
    AmbientLight(const Color& color) : Light(color) {}

    double lambertian(const Intersection& intersection) const override { return 0; }
    vec3 reflection(const Intersection& intersection) const override { return {}; }
    Ray castRayToLight(const Intersection& intersection) const override { return {}; }
};

#endif //RAYTRACER_AMBIENTLIGHT_H