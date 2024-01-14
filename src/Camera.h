#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "vec3.h"
#include "Ray.h"
#include <cmath>

class Camera {
    vec3 position;
    vec3 lookat;
    vec3 up;
    int horizontal_fov;
    int resolution_horizontal;
    int resolution_vertical;
    int max_bounces;

public:
    Camera(const vec3& position, const vec3& lookat, const vec3& up,
           int horizontal_fov, int resolution_horizontal, int resolution_vertical, int max_bounces)
            : position{position}, lookat{lookat}, up{up},
              horizontal_fov{horizontal_fov}, resolution_horizontal{resolution_horizontal},
              resolution_vertical{resolution_vertical}, max_bounces{max_bounces} {}

    const vec3& getPosition() const { return position; }
    const vec3& getLookAt() const { return lookat; }
    const vec3& getUp() const { return up; }
    int getHorizontalFOV() const { return horizontal_fov; }
    double getVerticalFOV() const { return horizontal_fov * (resolution_vertical / resolution_horizontal); }
    int getResolutionHorizontal() const { return resolution_horizontal; }
    int getResolutionVertical() const { return resolution_vertical; }
    int getMaxBounces() const { return max_bounces; }

    Ray* getRayToPixel(unsigned int u, unsigned int v) const {
        //normalize coordinates
        double xn = (u + 0.5) / resolution_horizontal;
        double yn = (v + 0.5) / resolution_vertical;

        //map to image plane
        double xi = 2 * xn - 1;
        double yi = 2 * yn - 1;

        //include FOV and image dimensions
        xi *= tan(getHorizontalFOV());
        yi *= tan(getVerticalFOV());

        //build ray direction and normalize
        vec3 direction = vec3(xi, yi, -1);
        direction = unit_vector(direction);

        return new Ray(position, direction);
    }
};

#endif //RAYTRACER_CAMERA_H
