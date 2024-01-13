#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

class Color {
    unsigned char _r;
    unsigned char _g;
    unsigned char _b;
public:
    Color() : _r{255}, _g{192}, _b{203} {}; //set pink as default color to spot artifacts more easily
    Color(unsigned char r, unsigned char g, unsigned char b) : _r{r}, _g{g}, _b{b} {};

    unsigned char r() const {return this->_r;}
    unsigned char g() const {return this->_g;}
    unsigned char b() const {return this->_b;}
};

#endif //RAYTRACER_COLOR_H
