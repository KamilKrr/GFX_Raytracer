#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H

#include "vec3.h"
#include "Material.h"
#include "matrix.h"

class Intersection;

class Ray;

class Surface {
protected:
    const Material* material;
    matrix translation;
    matrix rotation_x;
    matrix rotation_y;
    matrix rotation_z;
    matrix scaling;
    matrix inverse_translation;
    matrix inverse_rotation_x;
    matrix inverse_rotation_y;
    matrix inverse_rotation_z;
    matrix inverse_scaling;
    matrix object2world;
    matrix world2object;

public:
    explicit Surface(const Material* material)
            : material(material) {}
    virtual ~Surface() = default;

    virtual bool hit(const Ray& r, Intersection& intersection) const = 0;
    const Material* getMaterial() const { return material; }

    void translate(vec3 t) {
        translation = matrix::from_translation(t);
        inverse_translation = matrix::from_translation(-t);
        world2object = inverse_translation * world2object;
    }
    void scale(vec3 s) {
        scaling = matrix::from_scale(s);
        inverse_scaling = matrix::from_scale(1/s);
        world2object = inverse_scaling * world2object;
        object2world = object2world * inverse_scaling;
    }
    void rotateX(double r) {
        rotation_x = matrix::from_rotation_x(-r);
        inverse_rotation_x = matrix::from_rotation_x(r);
        world2object = inverse_rotation_x * world2object;
        object2world = object2world * rotation_x;
    }
    void rotateY(double r) {
        rotation_y = matrix::from_rotation_y(-r);
        inverse_rotation_y = matrix::from_rotation_y(r);
        world2object = inverse_rotation_y * world2object;
        object2world = object2world * rotation_y;
    }
    void rotateZ(double r) {
        rotation_z = matrix::from_rotation_z(-r);
        inverse_rotation_z = matrix::from_rotation_z(r);
        world2object = inverse_rotation_z * world2object;
        object2world = object2world * rotation_z;
    }

    matrix getModelMatrix(bool include_translation = true) const {
        if(include_translation)
            return world2object;
        return ignore_translation(world2object);
    }

    vec3 normal_to_world_space(vec3 normal) const {
        return unit_vector(object2world * normal);
    }
};

#endif //RAYTRACER_SURFACE_H
