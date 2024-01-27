#ifndef RAYTRACER_COLORMATERIAL_H
#define RAYTRACER_COLORMATERIAL_H

#include "Material.h"

class ColorMaterial : public Material {
    Color color;
public:
    ColorMaterial(const Color& color, double ka, double kd, double ks, int exponent,
                 double reflectance, double transmittance, double index_of_refraction)
            : Material{ka, kd, ks, exponent, reflectance, transmittance, index_of_refraction}, color{color} {}

    const Color& getColor() const { return color; }
    Color getColorAtTexel(point2 texel) const {
        return color;
    }
};

#endif //RAYTRACER_COLORMATERIAL_H
