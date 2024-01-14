#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Color.h"

class Material {
    Color color;
    struct Phong {
        double ka;
        double kd;
        double ks;
        int exponent;
    } phong;
    double reflectance;
    double transmittance;
    double index_of_refraction;

public:
    Material(const Color& color, double ka, double kd, double ks, int exponent,
             const double reflectance, double transmittance, float index_of_refraction)
            : color{color}, phong{ka, kd, ks, exponent},
              reflectance{reflectance}, transmittance{transmittance},
              index_of_refraction{index_of_refraction} {}
};

#endif // RAYTRACER_MATERIAL_H
