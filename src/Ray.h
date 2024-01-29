#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"
#include "Surface.h"


class Ray {
    point3 orig;
    vec3 dir;
    double min_distance = 0.003;
    double max_distance = std::numeric_limits<double>::infinity();
public:
    Ray() {}
    Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 origin() const  { return orig; }
    void displaceOrigin(vec3 d) { orig += d; }
    vec3 direction() const { return dir; }
    double getMinDistance() const { return min_distance; }
    double getMaxDistance() const { return max_distance; }
    void setMaxDistance(double max) { max_distance = max; }

    point3 at(double t) const {
        return orig + t*dir;
    }

    void to_object_space(const Surface& s) {
        point3 object_space_orig = s.getModelMatrix(true) * orig;
        vec3 object_space_dir = s.getModelMatrix(false) * dir;
        if(max_distance != infinity)
            max_distance = (object_space_orig - s.getModelMatrix() * (orig + dir * max_distance)).length();
        min_distance = (object_space_orig - s.getModelMatrix() * (orig + dir * min_distance)).length();

        orig = object_space_orig;
        dir = object_space_dir;
    }
};

#endif //RAYTRACER_RAY_H
