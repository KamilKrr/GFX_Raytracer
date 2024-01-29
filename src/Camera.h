#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "vec3.h"
#include "Ray.h"
#include "matrix.h"
#include <cmath>

class Camera {
    vec3 position;
    vec3 lookat;
    vec3 up;
    int horizontal_fov;
    int resolution_horizontal;
    int resolution_vertical;
    int max_bounces;
    int supersamples = 1;

    vec3 animPosition;
    vec3 animLookat;

    int frames = 1;
    int delay = 1;

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

    void animationStep(int frames_left) {
        position = position + (animPosition - position) / frames_left;
        lookat = lookat + (animLookat - lookat) / frames_left;
    }

    int getSupersamples() const {
        return supersamples;
    }
    void setSupersamples(int supersamples) {
        Camera::supersamples = supersamples;
    }

    const vec3 &getAnimPosition() const {
        return animPosition;
    }

    void setAnimPosition(const vec3 &animPosition) {
        Camera::animPosition = animPosition;
    }

    const vec3 &getAnimLookat() const {
        return animLookat;
    }

    void setAnimLookat(const vec3 &animLookat) {
        Camera::animLookat = animLookat;
    }

    int getFrames() const {
        return frames;
    }

    void setFrames(int frames) {
        Camera::frames = frames;
    }

    int getDelay() const {
        return delay;
    }

    void setDelay(int delay) {
        Camera::delay = delay;
    }

    Ray* getRayToPixel(unsigned int u, unsigned int v) const {
        point3 origin = point3(0, 0, 0);
        //normalize coordinates
        double xn = (u + 0.5) / resolution_horizontal;
        double yn = (v + 0.5) / resolution_vertical;

        //map to image plane
        double xi = 2 * xn - 1;
        double yi = 2 * yn - 1;

        //include FOV and image dimensions
        xi *= tan(degrees_to_radians(getHorizontalFOV()));
        yi *= tan(degrees_to_radians(getVerticalFOV()));

        //build ray direction and normalize
        vec3 direction = vec3(xi, yi, -1);
        direction = unit_vector(direction);

        matrix t = getTransformationMatrix();
        matrix r = getRotationMatrix();

        return new Ray(t * origin, unit_vector(r * direction));
    }

    matrix getTransformationMatrix() const {
        vec3 z = unit_vector(position - lookat);
        vec3 x = unit_vector(cross(up, z));
        vec3 y = unit_vector(cross(z, x));

        return {
            x.x(), y.x(), z.x(), position.x(),
            x.y(), y.y(), z.y(), position.y(),
            x.z(), y.z(), z.z(), position.z(),
            0, 0, 0, 1
        };
    }

    matrix getRotationMatrix() const {
        vec3 z = unit_vector(position - lookat);
        vec3 x = unit_vector(cross(up, z));
        vec3 y = unit_vector(cross(z, x));

        return {
                x.x(), y.x(), z.x(), 0,
                x.y(), y.y(), z.y(), 0,
                x.z(), y.z(), z.z(), 0,
                0, 0, 0, 1
        };
    }
};

#endif //RAYTRACER_CAMERA_H
