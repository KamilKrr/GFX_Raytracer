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
    std::vector<matrix> transforms;

public:
    explicit Surface(const Material* material)
            : material(material) {}
    virtual ~Surface() = default;

    virtual bool hit(const Ray& r, Intersection& intersection) const = 0;
    const Material* getMaterial() const { return material; }

    void translate(vec3 t) {
        translation = matrix::from_translation(t);
        inverse_translation = matrix::from_translation(-t);
        transforms.push_back(inverse_translation);
    }
    void scale(vec3 s) {
        scaling = matrix::from_scale(s);
        inverse_scaling = matrix::from_scale(1/s);
        transforms.push_back(inverse_scaling);
    }
    void rotateX(double r) {
        rotation_x = matrix::from_rotation_x(r);
        inverse_rotation_x = matrix::from_rotation_x(-r);
        transforms.push_back(inverse_rotation_x);
    }
    void rotateY(double r) {
        rotation_y = matrix::from_rotation_y(r);
        inverse_rotation_y = matrix::from_rotation_y(-r);
        transforms.push_back(inverse_rotation_y);
    }
    void rotateZ(double r) {
        rotation_z = matrix::from_rotation_z(r);
        inverse_rotation_z = matrix::from_rotation_z(-r);
        transforms.push_back(inverse_rotation_z);
    }

    matrix getModelMatrix(bool include_translation = true) const {
        matrix modelMatrix;
        for (auto it = transforms.rbegin(); it != transforms.rend(); ++it) {
            modelMatrix = modelMatrix * *it;
        }
        if(include_translation)
            return modelMatrix;
        return ignore_translation(modelMatrix);
    }

    vec3 normal_to_world_space(vec3 normal) const {
        normal = inverse_rotation_x * normal;
        normal = inverse_rotation_y * normal;
        normal = inverse_rotation_z * normal;
        normal = scaling * normal;
        normal = unit_vector(normal);

        return normal;
    }
};

#endif //RAYTRACER_SURFACE_H
