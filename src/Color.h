#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "../lib/pugixml/pugixml.hpp"

class Color {
    int _r;
    int _g;
    int _b;

public:
    Color() : _r{255}, _g{20}, _b{147} {} // set pink as default color to spot artifacts more easily

    Color(int r, int g, int b) : _r{r}, _g{g}, _b{b} {}

    Color(pugi::xml_node xml_color_node)
            : _r{static_cast<int>(std::stod(xml_color_node.attribute("_r").value()) * 255)},
              _g{static_cast<int>(std::stod(xml_color_node.attribute("_g").value()) * 255)},
              _b{static_cast<int>(std::stod(xml_color_node.attribute("_b").value()) * 255)} {}

    int r() const { return this->_r; }
    int g() const { return this->_g; }
    int b() const { return this->_b; }

    Color& operator+(const Color& other) {
        _r += other._r;
        _g += other._g;
        _b += other._b;
        return *this;
    }

    Color& operator*(double factor) {
        _r = static_cast<int>(_r * factor);
        _g = static_cast<int>(_g * factor);
        _b = static_cast<int>(_b * factor);
        return *this;
    }
};

Color operator*(const Color& lhs, double factor) {
    Color result = lhs;
    result = result * factor;
    return result;
}

#endif //RAYTRACER_COLOR_H
