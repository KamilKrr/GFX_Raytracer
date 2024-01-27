#ifndef RAYTRACER_SCENEPARSER_H
#define RAYTRACER_SCENEPARSER_H

#include "../lib/pugixml/pugixml.hpp"
#include "Scene.h"
#include "AmbientLight.h"
#include "Material.h"
#include "Surface.h"
#include "Sphere.h"
#include "ParallelLight.h"
#include "Mesh.h"
#include "WavefrontParser.h"
#include "PointLight.h"
#include <string>
#include <iostream>
#include <memory>
#include <cstring>

class SceneParser {
public:
    static Scene* parseScene(const std::string& filename) {
        pugi::xml_document doc;
        auto* scene = new Scene();

        pugi::xml_parse_result result = doc.load_file(filename.c_str(), pugi::parse_default);

        if (result) {
            // Access the scene root node
            pugi::xml_node xml_scene = doc.child("scene");

            scene->setOutputFile(xml_scene.attribute("output_file").value());

            // Background Color
            const auto* background_color = new Color(xml_scene.child("background_color"));
            scene->setBackgroundColor(background_color);

            //Camera
            pugi::xml_node xml_camera = xml_scene.child("camera");
            vec3* position = new vec3(xml_camera.child("position"));
            vec3* lookat = new vec3(xml_camera.child("lookat"));
            vec3* up = new vec3(xml_camera.child("up"));
            const auto* camera = new Camera(
                    *position,
                    *lookat,
                    *up,
                    std::stoi(xml_camera.child("horizontal_fov").attribute("angle").value()),
                    std::stoi(xml_camera.child("resolution").attribute("horizontal").value()),
                    std::stoi(xml_camera.child("resolution").attribute("vertical").value()),
                    std::stoi(xml_camera.child("max_bounces").attribute("n").value())
                );
            scene->setCamera(camera);

            //Lights
            pugi::xml_node xml_lights = xml_scene.child("lights");

            for (pugi::xml_node xml_light = xml_lights.first_child(); xml_light; xml_light = xml_light.next_sibling()) {
                auto* color = new Color(xml_light.child("color"));

                if (std::strcmp(xml_light.name(), "ambient_light") == 0) {
                    auto light = std::make_shared<AmbientLight>(*color);
                    scene->setAmbientLight(light);
                }else if (std::strcmp(xml_light.name(), "parallel_light") == 0) {
                    const vec3* light_direction = new vec3(xml_light.child("direction"));
                    auto light = std::make_unique<ParallelLight>(*color, *light_direction);

                    scene->addLight(std::move(light));
                }else if (std::strcmp(xml_light.name(), "point_light") == 0) {
                    const point3* light_position = new point3(xml_light.child("position"));
                    auto light = std::make_unique<PointLight>(*color, *light_position);

                    scene->addLight(std::move(light));
                }
            }

            //Surfaces
            pugi::xml_node xml_surfaces = xml_scene.child("surfaces");

            for (pugi::xml_node xml_surface = xml_surfaces.first_child(); xml_surface; xml_surface = xml_surface.next_sibling()) {

                pugi::xml_node xml_surface_material_solid = xml_surface.child("material_solid");

                const Color* material_color = new Color(xml_surface_material_solid.child("color"));
                const Material* surface_material = new Material(
                        *material_color,
                        std::stod(xml_surface_material_solid.child("phong").attribute("ka").value()),
                        std::stod(xml_surface_material_solid.child("phong").attribute("kd").value()),
                        std::stod(xml_surface_material_solid.child("phong").attribute("ks").value()),
                        std::stoi(xml_surface_material_solid.child("phong").attribute("exponent").value()),
                        std::stod(xml_surface_material_solid.child("reflectance").attribute("r").value()),
                        std::stod(xml_surface_material_solid.child("transmittance").attribute("t").value()),
                        std::stof(xml_surface_material_solid.child("refraction").attribute("iof").value())
                );

                if (std::strcmp(xml_surface.name(), "sphere") == 0) {
                    const auto* surface_position = new vec3(xml_surface.child("position"));

                    double sphere_radius = std::stod(xml_surface.attribute("radius").value());

                    auto sphere = std::make_unique<Sphere>(
                            *surface_position,
                            *surface_material,
                            sphere_radius
                            );

                    scene->addSurface(std::move(sphere));
                }else if (std::strcmp(xml_surface.name(), "mesh") == 0) {
                    //construct path relative to the scene.xml file
                    std::filesystem::path input_filename_directory = std::filesystem::path(filename).parent_path();
                    std::string xml_surface_filename = (input_filename_directory / xml_surface.attribute("name").value()).string();

                    auto mesh = std::make_shared<Mesh>(
                            *surface_material
                    );

                    WavefrontParser::importWavefrontMesh(xml_surface_filename, mesh);
                    scene->addSurface(std::move(mesh));
                }
            }
        } else {
            std::cerr << "Failed to load XML file. Error description: " << result.description() << std::endl;
        }

        return scene;
    }
};

#endif //RAYTRACER_SCENEPARSER_H
