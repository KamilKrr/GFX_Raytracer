#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include "Surface.h"
#include "Ray.h"
#include "Face.h"

class Mesh : public Surface {
    std::vector<shared_ptr<Face>> faces;

public:
    explicit Mesh(const Material& material)
            : Surface{material} {}

    bool hit(const Ray& r, Intersection& intersection) const override {
        for(auto face : faces) {
            if(rayTriangleIntersect(r, intersection, face)){
                return true;
            }
        }
        return false;
    }

    bool rayTriangleIntersect(const Ray& r, Intersection& intersection, std::shared_ptr<Face> face) const
    {
        vec3 v0v1 = face->v1 - face->v0;
        vec3 v0v2 = face->v2 - face->v0;
        vec3 pvec = cross(r.direction(), v0v2);
        float det = dot(v0v1, pvec);

        if (fabs(det) < 0.0000001) return false;

        float invDet = 1 / det;

        vec3 tvec = r.origin() - face->v0;
        double u = dot(tvec, pvec) * invDet;
        if (u < 0 || u > 1) return false;

        vec3 qvec = cross(tvec, v0v1);
        double v = dot(r.direction(), qvec) * invDet;
        if (v < 0 || u + v > 1) return false;

        double t = dot(v0v2, qvec) * invDet;

        if(t > r.getMaxDistance()) return false;

        intersection.setDistance(t);
        intersection.setPosition(r.at(t));
        intersection.setNormal(face->vn0);
        intersection.setMaterial(&this->material);

        return true;
    }

    void setFaces(const std::vector<shared_ptr<Face>> &faces) {
        Mesh::faces = faces;
    }
};

#endif //RAYTRACER_MESH_H
