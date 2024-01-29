#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "../lib/pugixml/pugixml.hpp"
#include "vec3.h"

class Color {
    double _r;
    double _g;
    double _b;

public:
    Color() : _r{1.0}, _g{1.1}, _b{1.5} {} // set pink as default color to spot artifacts more easily

    Color(double r, double g, double b) : _r{r}, _g{g}, _b{b} {}

    Color(pugi::xml_node xml_color_node)
            : _r{std::stod(xml_color_node.attribute("r").value())},
              _g{std::stod(xml_color_node.attribute("g").value())},
              _b{std::stod(xml_color_node.attribute("b").value())} {}

    Color(vec3 v) : _r{(v.x())}, _g{v.y()}, _b{v.z()} {}

    double r() const { return this->_r; }
    double g() const { return this->_g; }
    double b() const { return this->_b; }

    Color& operator+(const Color& other) {
        _r += other._r;
        _g += other._g;
        _b += other._b;
        return *this;
    }

    Color& operator*(double factor) {
        _r = _r * factor;
        _g = _g * factor;
        _b = _b * factor;
        return *this;
    }

    Color& operator/(double factor) {
        _r = _r / factor;
        _g = _g / factor;
        _b = _b / factor;
        return *this;
    }
};

Color operator*(const Color& lhs, double factor) {
    Color result = lhs;
    result = result * factor;
    return result;
}

Color operator/(const Color& lhs, double factor) {
    Color result = lhs;
    result = result / factor;
    return result;
}


Color operator*(const Color& lhs, const Color& rhs) {
    return {
        lhs.r() * rhs.r(),
        lhs.g() * rhs.g(),
        lhs.b() * rhs.b()
    };
}

inline std::ostream& operator<<(std::ostream &out, const Color &c) {
    return out << c.r() << ' ' << c.g() << ' ' << c.b();
}

#endif //RAYTRACER_COLOR_H
