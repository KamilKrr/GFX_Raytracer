#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H

#include "Light.h"

class AmbientLight : public Light {
public:
    AmbientLight(const Color& color) : Light(color) {}
};

#endif //RAYTRACER_AMBIENTLIGHT_H