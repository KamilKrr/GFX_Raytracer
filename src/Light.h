#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "Color.h"
#include "Intersection.h"

class Light {
protected:
    Color color;

public:
    Light(const Color& color) : color{color} {}
    virtual ~Light() = default;

    const Color& getColor() const { return color; }
    virtual double lambertian(const Intersection& intersection) const = 0;
    virtual vec3 reflection(const Intersection& intersection) const = 0;
    virtual Ray castRayToLight(const Intersection& intersection) const = 0;
};

#endif //RAYTRACER_LIGHT_H