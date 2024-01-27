#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Color.h"
#include "point2.h"

class Material {
    struct Phong { double ka, kd, ks; int exponent; } phong;
    double reflectance, transmittance, index_of_refraction;

public:
    Material(double ka, double kd, double ks, int exponent,
             double reflectance, double transmittance, double index_of_refraction)
            : phong{ka, kd, ks, exponent},
              reflectance{reflectance}, transmittance{transmittance},
              index_of_refraction{index_of_refraction} {}

    double getKa() const { return phong.ka; }
    double getKd() const { return phong.kd; }
    double getKs() const { return phong.ks; }
    int getExponent() const { return phong.exponent; }
    double getReflectance() const { return reflectance; }
    double getTransmittance() const { return transmittance; }
    double getIndexOfRefraction() const { return index_of_refraction; }
    virtual Color getColorAtTexel(point2 texel) const = 0;
};

#endif // RAYTRACER_MATERIAL_H
