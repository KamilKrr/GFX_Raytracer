#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include "vec3.h"
#include "Material.h"

class Intersection {
    point3 position;
    double distance;
    vec3 normal;
    const Material* material = nullptr;

public:
    const point3& getPosition() const { return position; }
    double getDistance() const { return distance; }
    const vec3& getNormal() const { return normal; }
    const Material* getMaterial() const { return material; }

    void setPosition(const point3& pos) { position = pos; }
    void setDistance(double dist) { distance = dist; }
    void setNormal(const vec3& norm) { normal = norm; }
    void setMaterial(const Material* mat) { material = mat; }
};

#endif //RAYTRACER_INTERSECTION_H
