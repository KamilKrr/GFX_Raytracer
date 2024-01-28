#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H

#include <cmath>
#include <iostream>
#include "vec3.h"

class matrix {
public:
    double m[4][4];
    matrix() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }

    matrix(double m00, double m01, double m02, double m03,
           double m10, double m11, double m12, double m13,
           double m20, double m21, double m22, double m23,
           double m30, double m31, double m32, double m33) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    static matrix from_translation(vec3 t) {
        matrix m;
        m.m[0][3] = t.x();
        m.m[1][3] = t.y();
        m.m[2][3] = t.z();
        return m;
    }

    static matrix from_scale(vec3 s) {
        matrix m;
        m.m[0][0] = s.x();
        m.m[1][1] = s.y();
        m.m[2][2] = s.z();
        return m;
    }

    static matrix from_rotation_x(double t) {
        double angle = degrees_to_radians(t);
        matrix m;
        m.m[1][1] = cos(angle);
        m.m[2][2] = cos(angle);
        m.m[1][2] = sin(angle);
        m.m[2][1] = -sin(angle);

        return m;
    }

    static matrix from_rotation_y(double t) {
        double angle = degrees_to_radians(t);
        matrix m;
        m.m[0][0] = cos(angle);
        m.m[2][2] = cos(angle);
        m.m[0][2] = -sin(angle);
        m.m[2][0] = sin(angle);

        return m;
    }

    static matrix from_rotation_z(double t) {
        double angle = degrees_to_radians(t);
        matrix m;
        m.m[0][0] = cos(angle);
        m.m[1][1] = cos(angle);
        m.m[0][1] = sin(angle);
        m.m[1][0] = -sin(angle);

        return m;
    }
};

inline std::ostream& operator<<(std::ostream& out, const matrix& mat) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            out << mat.m[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}


inline vec3 operator*(const matrix& mat, const vec3& v) {
    double x = mat.m[0][0] * v.x() + mat.m[0][1] * v.y() + mat.m[0][2] * v.z() + mat.m[0][3];
    double y = mat.m[1][0] * v.x() + mat.m[1][1] * v.y() + mat.m[1][2] * v.z() + mat.m[1][3];
    double z = mat.m[2][0] * v.x() + mat.m[2][1] * v.y() + mat.m[2][2] * v.z() + mat.m[2][3];
    double w = mat.m[3][0] * v.x() + mat.m[3][1] * v.y() + mat.m[3][2] * v.z() + mat.m[3][3];

    if (w != 0.0) {
        return {x / w, y / w, z / w};
    }

    return {0.0, 0.0, 0.0};
}

inline matrix operator*(const matrix& mat1, const matrix& mat2) {
    matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] =
                    mat1.m[i][0] * mat2.m[0][j] +
                    mat1.m[i][1] * mat2.m[1][j] +
                    mat1.m[i][2] * mat2.m[2][j] +
                    mat1.m[i][3] * mat2.m[3][j];
        }
    }
    return result;
}

inline matrix ignore_translation(const matrix& m) {
    return {
        m.m[0][0], m.m[0][1], m.m[0][2], 0,
        m.m[1][0], m.m[1][1], m.m[1][2], 0,
        m.m[2][0], m.m[2][1], m.m[2][2], 0,
        m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]
    };
}

inline bool operator==(const matrix& mat1, const matrix& mat2) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (mat1.m[i][j] != mat2.m[i][j]) {
                return false;
            }
        }
    }
    return true;
}

inline bool operator!=(const matrix& mat1, const matrix& mat2) {
    return !(mat1 == mat2);
}

#endif //RAYTRACER_MATRIX_H
