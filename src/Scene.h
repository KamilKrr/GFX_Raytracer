#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Color.h"
#include "Camera.h"
#include "Light.h"
#include "AmbientLight.h"
#include "Surface.h"
#include <utility>
#include <vector>
#include <memory>

class Scene {
    std::string output_file {"default.png"};
    const Color* background_color { new Color() };
    Camera* camera;
    std::shared_ptr<AmbientLight> ambientLight;
    std::vector<std::shared_ptr<Light>> lights;
    std::vector<std::shared_ptr<Surface>> surfaces;

    int cframe = 1;

    bool motion_blur = true;

public:
    void setOutputFile(std::string f) { this->output_file = std::move(f); }
    std::string getOutputFile() const { return this->output_file; }

    void setBackgroundColor(const Color* c) { this->background_color = c; }
    const Color* getBackgroundColor() const { return this->background_color; }

    void setCamera(Camera* c) { this->camera = c; }
    const Camera* getCamera() const { return this->camera; }

    void addLight(std::shared_ptr<Light> l) { this->lights.push_back(std::move(l)); }

    void setAmbientLight(const std::shared_ptr<AmbientLight> l) {this->ambientLight = l; }
    std::shared_ptr<AmbientLight> getAmbientLight() const { return this->ambientLight; }

    void animationStep() {
        if(cframe < camera->getFrames())
            camera->animationStep(camera->getFrames()-cframe);

        for(auto s : surfaces) {
            if(cframe < s->getBlurFrames())
                s->animationStep(s->getBlurFrames()-cframe);
        }
        ++cframe;
    }


    const std::vector<std::shared_ptr<Light>>& getLights() const {
        return this->lights;
    }

    void addSurface(std::shared_ptr<Surface> s) {
        this->surfaces.push_back(std::move(s));
    }

    const std::vector<std::shared_ptr<Surface>>& getSurfaces() const {
        return this->surfaces;
    }

    int getFrames() const {
        int frames = camera->getFrames();
        for(auto surface : surfaces) {
            if(surface->getBlurFrames() > frames) frames = surface->getBlurFrames();
        }
        return frames;
    }

    bool hasMotionBlur() const {
        for(auto surface : surfaces) {
            if(surface->hasMotionBlur()) return true;
        }
        return false;
    }
};

#endif //RAYTRACER_SCENE_H
