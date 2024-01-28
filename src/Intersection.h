#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include "vec3.h"
#include "Material.h"
#include "Ray.h"

class Intersection {
    point3 position;
    double distance;
    vec3 normal;
    const Material* material = nullptr;
    Color color;

public:
    const point3& getPosition() const { return position; }
    double getDistance() const { return distance; }
    const vec3& getNormal() const { return normal; }
    const Material* getMaterial() const { return material; }
    const Color getColor() const { return color; }

    void setPosition(const point3& pos) { position = pos; }
    void setDistance(double dist) { distance = dist; }
    void setNormal(const vec3& norm) { normal = unit_vector(norm); }
    void setMaterial(const Material* mat) { material = mat; }
    void setColor(Color col) { color = col; }

    void to_world_space(const Ray& world_ray, const Surface& surface) {
        position = world_ray.at(distance);
        normal = surface.normal_to_world_space(normal);
    }

};

#endif //RAYTRACER_INTERSECTION_H
