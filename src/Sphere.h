#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Surface.h"
#include "Intersection.h"

class Sphere : public Surface {
    vec3 position;
    double radius;

public:
    Sphere(const vec3& position, const Material& material, double radius)
            : Surface{material}, position{position}, radius{radius} {}

    bool hit(const Ray& r, Intersection& intersection) const override {
        vec3 oc = r.origin() - this->position;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;

        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root <= r.getMinDistance() || r.getMaxDistance() <= root) {
            root = (-half_b + sqrtd) / a;
            if (root <= r.getMinDistance() || r.getMaxDistance() <= root)
                return false;
        }

        intersection.setDistance(root);
        intersection.setPosition(r.at(root));
        intersection.setNormal(vec3((intersection.getPosition() - position) / radius));
        intersection.setMaterial(&this->material);

        return true;
    }
};

#endif //RAYTRACER_SPHERE_H
