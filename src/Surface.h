#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H

#include "vec3.h"
#include "Material.h"
#include "Intersection.h"
#include "Ray.h"

class Surface {
protected:
    Material material;

public:
    explicit Surface(const Material& material)
            : material{material} {}
    virtual ~Surface() = default;

    virtual bool hit(const Ray& r, Intersection& intersection) const = 0;
    Material& getMaterial() { return material; }
};

#endif //RAYTRACER_SURFACE_H