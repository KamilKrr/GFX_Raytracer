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
    void setPixelColor(unsigned int x, unsigned int y, const Color& color) { setPixelColor(y * width + x, color); }
    Color getColor(unsigned int x, unsigned int y) const { return colors[y * width + x]; }

    friend inline Image operator+(const Image& lhs, const Image& rhs);
    friend inline Image operator/(const Image& lhs, double value);
};

inline Image operator+(const Image& lhs, const Image& rhs) {
    Image result = lhs;
    for (unsigned int i = 0; i < result.colors.size(); ++i) {
        result.colors.at(i) = lhs.colors.at(i) + rhs.colors.at(i);
    }
    return result;
}

inline Image operator/(const Image& lhs, double value) {
    Image result = lhs;
    for (unsigned int i = 0; i < result.colors.size(); ++i) {
        result.colors.at(i) = lhs.colors.at(i) / value;
    }
    return result;
}


#endif //RAYTRACER_IMAGE_H
