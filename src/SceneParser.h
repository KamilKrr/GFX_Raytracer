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
#include "ImageDecoder.h"
#include "ColorMaterial.h"
#include "TextureMaterial.h"
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
            auto* camera = new Camera(
                    *position,
                    *lookat,
                    *up,
                    std::stoi(xml_camera.child("horizontal_fov").attribute("angle").value()),
                    std::stoi(xml_camera.child("resolution").attribute("horizontal").value()),
                    std::stoi(xml_camera.child("resolution").attribute("vertical").value()),
                    std::stoi(xml_camera.child("max_bounces").attribute("n").value())
                );

            //Supersampling
            pugi::xml_node xml_supersamples = xml_camera.child("supersamples");
            if(xml_supersamples != nullptr){
                camera->setSupersamples(std::stoi(xml_supersamples.attribute("n").value()));
            }

            //Animations
            pugi::xml_node xml_anim = xml_camera.child("anim");
            if(xml_anim != nullptr){
                scene->setFrames(std::stoi(xml_anim.attribute("frames").value()));
                scene->setDelay(std::stoi(xml_anim.attribute("delay").value()));

                camera->setAnimPosition(xml_anim.child("position"));
                camera->setAnimLookat(xml_anim.child("lookat"));
            }
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

                const Material* surface_material;

                pugi::xml_node xml_surface_material_solid = xml_surface.child("material_solid");
                pugi::xml_node xml_surface_material_textured = xml_surface.child("material_textured");

                if(xml_surface_material_solid != nullptr) {
                    const auto material_color = Color(xml_surface_material_solid.child("color"));
                    surface_material = new ColorMaterial(
                            material_color,
                            std::stod(xml_surface_material_solid.child("phong").attribute("ka").value()),
                            std::stod(xml_surface_material_solid.child("phong").attribute("kd").value()),
                            std::stod(xml_surface_material_solid.child("phong").attribute("ks").value()),
                            std::stoi(xml_surface_material_solid.child("phong").attribute("exponent").value()),
                            std::stod(xml_surface_material_solid.child("reflectance").attribute("r").value()),
                            std::stod(xml_surface_material_solid.child("transmittance").attribute("t").value()),
                            std::stof(xml_surface_material_solid.child("refraction").attribute("iof").value())
                    );
                }else if(xml_surface_material_textured != nullptr){
                    std::string xml_surface_texture = xml_surface_material_textured.child("texture").attribute("name").value();
                    //construct path relative to the scene.xml file
                    std::filesystem::path input_filename_directory = std::filesystem::path(filename).parent_path();
                    std::string xml_surface_filename = (input_filename_directory / xml_surface_texture).string();

                    Image texture = ImageDecoder::importImage(xml_surface_filename);
                    surface_material = new TextureMaterial(
                            texture,
                            std::stod(xml_surface_material_textured.child("phong").attribute("ka").value()),
                            std::stod(xml_surface_material_textured.child("phong").attribute("kd").value()),
                            std::stod(xml_surface_material_textured.child("phong").attribute("ks").value()),
                            std::stoi(xml_surface_material_textured.child("phong").attribute("exponent").value()),
                            std::stod(xml_surface_material_textured.child("reflectance").attribute("r").value()),
                            std::stod(xml_surface_material_textured.child("transmittance").attribute("t").value()),
                            std::stof(xml_surface_material_textured.child("refraction").attribute("iof").value())
                    );
                }

                shared_ptr<Surface> surface;

                if (std::strcmp(xml_surface.name(), "sphere") == 0) {
                    const auto* surface_position = new vec3(xml_surface.child("position"));

                    double sphere_radius = std::stod(xml_surface.attribute("radius").value());

                    surface = std::make_shared<Sphere>(
                            *surface_position,
                            surface_material,
                            sphere_radius
                            );
                }else if (std::strcmp(xml_surface.name(), "mesh") == 0) {
                    //construct path relative to the scene.xml file
                    std::filesystem::path input_filename_directory = std::filesystem::path(filename).parent_path();
                    std::string xml_surface_filename = (input_filename_directory / xml_surface.attribute("name").value()).string();

                    auto mesh = std::make_shared<Mesh>(
                            surface_material
                    );

                    WavefrontParser::importWavefrontMesh(xml_surface_filename, mesh);
                    surface = mesh;
                }

                pugi::xml_node xml_surface_transform = xml_surface.child("transform");
                if(xml_surface_transform){
                    for (pugi::xml_node xml_surface_elemental_transform = xml_surface_transform.first_child(); xml_surface_elemental_transform; xml_surface_elemental_transform = xml_surface_elemental_transform.next_sibling()) {
                        if (std::strcmp(xml_surface_elemental_transform.name(), "translate") == 0) {
                            vec3 translation = vec3(xml_surface_elemental_transform);
                            surface->translate(translation);
                        }else if (std::strcmp(xml_surface_elemental_transform.name(), "scale") == 0){
                            vec3 scale = vec3(xml_surface_elemental_transform);
                            surface->scale(scale);
                        }else if (std::strcmp(xml_surface_elemental_transform.name(), "rotateX") == 0){
                            surface->rotateX(std::stod(xml_surface_elemental_transform.attribute("theta").value()));
                        }else if (std::strcmp(xml_surface_elemental_transform.name(), "rotateY") == 0){
                            surface->rotateY(std::stod(xml_surface_elemental_transform.attribute("theta").value()));
                        }else if (std::strcmp(xml_surface_elemental_transform.name(), "rotateZ") == 0){
                            surface->rotateZ(std::stod(xml_surface_elemental_transform.attribute("theta").value()));
                        }
                    }
                }


                scene->addSurface(std::move(surface));
            }
        } else {
            std::cerr << "Failed to load XML file. Error description: " << result.description() << std::endl;
        }

        return scene;
    }
};

#endif //RAYTRACER_SCENEPARSER_H
