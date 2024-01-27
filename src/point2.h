#ifndef RAYTRACER_POINT2_H
#define RAYTRACER_POINT2_H

class point2 {
public:
    double e[22];

    point2() : e{0, 0} {}
    point2(double e0, double e1) : e{e0, e1} {}
    point2(const std::string& e0, const std::string& e1) : e{std::stod(e0), std::stod(e1)} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
};

inline point2 operator+(const point2 &u, const point2 &v) {
    return {u.e[0] + v.e[0], u.e[1] + v.e[1]};
}

inline point2 operator*(double t, const point2 &v) {
    return {t*v.e[0], t*v.e[1]};
}

inline point2 operator*(const point2 &v, double t) {
    return t * v;
}

inline std::ostream& operator<<(std::ostream &out, const point2 &v) {
    return out << v.e[0] << ' ' << v.e[1];
}

#endif //RAYTRACER_POINT2_H
