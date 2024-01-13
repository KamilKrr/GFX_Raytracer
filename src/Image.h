#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <utility>
#include <vector>
#include "Color.h"

class Image {
    std::string name;
    unsigned int width;
    unsigned int height;
    std::vector<Color> colors;

public:
    Image(std::string name, unsigned int width, unsigned int height) : name{std::move(name)}, width{width}, height{height}, colors{std::vector<Color>(width * height)} {}
    unsigned int getWidth() const {return this->width;}
    unsigned int getHeight() const {return this->height;}
    std::vector<Color> getColors() const {return this->colors;};
    std::string getName() const {return this->name;};
    void setPixelColor(unsigned int index, const Color& color) {this->colors[index] = color;}

};

#endif //RAYTRACER_IMAGE_H
