#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Color.h"
#include "Camera.h"
#include "Light.h"
#include "AmbientLight.h"
#include "Surface.h"
#include <utility>
#include <vector>

class Scene {
    std::string output_file {"default.png"};
    const Color* background_color { new Color() };
    const Camera* camera;
    const AmbientLight* ambientLight;
    std::vector<Light> lights;
    std::vector<Surface> surfaces;

public:
    void setOutputFile(std::string f) { this->output_file = std::move(f); }
    std::string getOutputFile() const { return this->output_file; }

    void setBackgroundColor(const Color* c) { this->background_color = c; }
    const Color* getBackgroundColor() const { return this->background_color; }

    void setCamera(const Camera* c) { this->camera = c; }
    const Camera* getCamera() const { return this->camera; }

    void addLight(const Light& l) { this->lights.push_back(l); }
    void setAmbientLight(const AmbientLight& l) {this->ambientLight = &l; }

    void addSurface(const Surface& s) { this->surfaces.push_back(s); }

};

#endif //RAYTRACER_SCENE_H
