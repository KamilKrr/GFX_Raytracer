#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Surface.h"

class Sphere : public Surface {
    double radius;

public:
    Sphere(const vec3& position, const Material& material, double radius)
            : Surface{position, material}, radius{radius} {}
};

#endif //RAYTRACER_SPHERE_H
