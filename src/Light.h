#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "Color.h"

class Light {
protected:
    Color color;

public:
    Light(const Color& color) : color{color} {}

    const Color& getColor() const { return color; }
};

#endif //RAYTRACER_LIGHT_H