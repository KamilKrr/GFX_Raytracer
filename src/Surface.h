#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H

#include "vec3.h"
#include "Material.h"
#include "Intersection.h"

class Surface {
protected:
    vec3 position;
    Material material;

public:
    Surface(const vec3& position, const Material& material)
            : position{position}, material{material} {}
    virtual ~Surface() = default;
    virtual bool hit(const Ray& r, Intersection& intersection) const = 0;
    Material& getMaterial() { return material; }
};

#endif //RAYTRACER_SURFACE_H