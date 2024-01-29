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
    matrix object2world;
    matrix world2object;
    vec3 blur_motion;
    int blur_frames = 0;

public:
    explicit Surface(const Material* material)
            : material(material) {}
    virtual ~Surface() = default;

    virtual bool hit(const Ray& r, Intersection& intersection) const = 0;
    const Material* getMaterial() const { return material; }

    void setBlurMotion(vec3 bm) {
        blur_motion = bm;
    }

    void setBlurFrames(int bf) {
        blur_frames = bf;
    }

    int getBlurFrames() const {
        return blur_frames;
    }

    bool hasMotionBlur() const {
        return (bool)blur_motion;
    }

    void translate(vec3 t) {
        world2object = matrix::from_translation(-t) * world2object;
    }
    void scale(vec3 s) {
        matrix inverse_scaling = matrix::from_scale(1/s);
        world2object = inverse_scaling * world2object;
        object2world = object2world * inverse_scaling;
    }
    void rotateX(double r) {
        world2object = matrix::from_rotation_x(r) * world2object;
        object2world = object2world * matrix::from_rotation_x(-r);
    }
    void rotateY(double r) {
        world2object = matrix::from_rotation_y(r) * world2object;
        object2world = object2world * matrix::from_rotation_y(-r);
    }
    void rotateZ(double r) {
        world2object = matrix::from_rotation_z(r) * world2object;
        object2world = object2world * matrix::from_rotation_z(-r);
    }

    matrix getModelMatrix(bool include_translation = true) const {
        if(include_translation)
            return world2object;
        return ignore_translation(world2object);
    }

    vec3 normal_to_world_space(vec3 normal) const {
        return unit_vector(object2world * normal);
    }

    void animationStep(int frames_left) {
        translate(blur_motion);
    }
};

#endif //RAYTRACER_SURFACE_H
