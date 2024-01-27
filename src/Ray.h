#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

class Ray {
    point3 orig;
    vec3 dir;
    double min_distance = 0;
    double max_distance = std::numeric_limits<double>::infinity();
public:
    Ray() {}
    Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 origin() const  { return orig; }
    vec3 direction() const { return dir; }
    double getMinDistance() const { return min_distance; }
    double getMaxDistance() const { return max_distance; }
    void setMaxDistance(double max) { max_distance = max; }

    point3 at(double t) const {
        return orig + t*dir;
    }
};

#endif //RAYTRACER_RAY_H
