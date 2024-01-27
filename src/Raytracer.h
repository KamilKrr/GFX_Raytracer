#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Scene.h"
#include "Image.h"
#include "ImageExporter.h"
#include "Ray.h"

class Raytracer {
    const Scene* scene;
    Image* image;

public:
    void render() {
        for (unsigned y = 0; y < image->getHeight(); ++y) {
            for (unsigned x = 0; x < image->getWidth(); ++x) {
                const auto ray = scene->getCamera()->getRayToPixel(x, y);
                const auto color = trace(*ray);
                image->setPixelColor(x, y, color);
            }
        }
    }

    Color trace(const Ray& ray, int depth = 0) const {
        Intersection intersection;

        for (const auto& surface : scene->getSurfaces()) {
            if (surface->hit(ray, intersection)) {
                auto ambientColor = intersection.getMaterial()->getColor() * intersection.getMaterial()->getKa();
                auto color = ambientColor;

                for (const auto& light : scene->getLights()) {
                    //ignore lights that are "behind" objects -> this is responsible for shadows
                    if(!cast_shadowray(intersection, *light)){
                        color = color + illuminate(&ray, intersection, light);
                    }
                }

                if(depth > 0){
                    return color;
                }

                auto reflected_color = Color(0, 0, 0);
                auto refracted_color = Color(0, 0, 0);

                if(intersection.getMaterial()->getReflectance() > 0){
                    const auto reflected_ray = get_reflected_ray(ray, intersection);
                    reflected_color = trace(reflected_ray, depth + 1) * intersection.getMaterial()->getReflectance();
                }

                color = color * (1 - intersection.getMaterial()->getReflectance() - intersection.getMaterial()->getTransmittance())
                        + reflected_color + refracted_color;
                return color;
            }
        }

        return *scene->getBackgroundColor();
    }

    Color illuminate(const Ray* ray, Intersection& intersection, const std::shared_ptr<Light> light) const {
        double lambertian = light->lambertian(intersection);

        auto diffuseColor = intersection.getMaterial()->getColor() * intersection.getMaterial()->getKd() * lambertian;

        if(lambertian > 0) {
            vec3 relection = light->reflection(intersection);
            double specAngle = std::max(dot(relection, -ray->direction()), 0.0);
            double specular = pow(specAngle, intersection.getMaterial()->getExponent());
            auto specularColor = light->getColor() * intersection.getMaterial()->getKs() * specular;

            return diffuseColor + specularColor;
        }

        return diffuseColor;
    }

    bool cast_shadowray(const Intersection& intersection, const Light& light) const {
        Ray ray = light.castRayToLight(intersection);
        Intersection shadowRayIntersection;

        for (const auto& surface : scene->getSurfaces()) {
            if (surface->hit(ray, shadowRayIntersection)) {
                if(shadowRayIntersection.getDistance() < ray.getMinDistance()) continue;
                return true;
            }
        }
        return false;
    }

    Ray get_reflected_ray(const Ray& ray, const Intersection& intersection) const {
        vec3 r = unit_vector(reflect(ray.direction(), intersection.getNormal()));
        return {intersection.getPosition(), r};
    }


    void output() {
        ImageExporter::exportImage(*image);
        std::cout << "Successfully rendered image " << this->image->getName() << std::endl;
    }

    void initialize(const Scene* s) {
        delete image;

        this->scene = s;
        this->image = new Image(this->scene->getOutputFile(), this->scene->getCamera()->getResolutionHorizontal(), this->scene->getCamera()->getResolutionVertical());
    }

    ~Raytracer() {
        delete image;
    }
};

#endif
