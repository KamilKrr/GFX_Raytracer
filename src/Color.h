#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "../lib/pugixml/pugixml.hpp"

class Color {
    unsigned char _r;
    unsigned char _g;
    unsigned char _b;
public:
    Color() : _r{255}, _g{20}, _b{147} {}; //set pink as default color to spot artifacts more easily
    Color(unsigned char r, unsigned char g, unsigned char b) : _r{r}, _g{g}, _b{b} {};
    Color(pugi::xml_node xml_color_node) :
        _r{static_cast<unsigned char>(std::stoi(xml_color_node.attribute("_r").value()))},
        _g{static_cast<unsigned char>(std::stoi(xml_color_node.attribute("_g").value()))},
        _b{static_cast<unsigned char>(std::stoi(xml_color_node.attribute("_b").value()))}
        {};

    unsigned char r() const {return this->_r;}
    unsigned char g() const {return this->_g;}
    unsigned char b() const {return this->_b;}
};

#endif //RAYTRACER_COLOR_H
