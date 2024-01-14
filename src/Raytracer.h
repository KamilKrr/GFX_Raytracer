#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Scene.h"
#include "Image.h"
#include "ImageExporter.h"

class Raytracer {
    const Scene* scene;
    Image* image;

public:
    void render() {
        for (unsigned y = 0; y < image->getHeight(); ++y) {
            for (unsigned x = 0; x < image->getWidth(); ++x) {

                const Color* color = trace();
                image->setPixelColor(x, y, *color);

            }
        }
    }

    const Color* trace() const {
        return scene->getBackgroundColor();
    }

    void output() {
        ImageExporter::exportImage(*image);
        std::cout << "Successfully created image " << this->image->getName() << std::endl;
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
