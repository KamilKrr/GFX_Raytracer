#ifndef RAYTRACER_TEXTUREMATERIAL_H
#define RAYTRACER_TEXTUREMATERIAL_H

#include "Material.h"
#include "Image.h"

class TextureMaterial : public Material {
    Image texture;
public:
    TextureMaterial(const Image& texture, double ka, double kd, double ks, int exponent,
                  double reflectance, double transmittance, double index_of_refraction)
            : Material{ka, kd, ks, exponent, reflectance, transmittance, index_of_refraction}, texture{texture} {}

    const Image& getTexture() const { return texture; }
    Color getColorAtTexel(point2 texel) const {
        return texture.getColor(texel.x() * texture.getWidth(), texel.y() * texture.getHeight());
    }
};


#endif //RAYTRACER_TEXTUREMATERIAL_H
