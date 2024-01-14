#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H

#include "vec3.h"
#include "Material.h"

class Surface {
    vec3 position;
    Material material;

public:
    Surface(const vec3& position, const Material& material)
            : position{position}, material{material} {}
};

#endif //RAYTRACER_SURFACE_H