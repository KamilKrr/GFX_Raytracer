#include <iostream>
#include <vector>

#include "src/Raytracer.h"
#include "src/SceneParser.h"
#include <filesystem>

int main() {
    std::cout << "Enter the filepath for the scene XML file relative to your current path (" << std::filesystem::current_path() << "): ";
    std::string filePath;
    //std::cin >> filePath;
    filePath = "../scenes/exampletest.xml";

    auto* scene = SceneParser::parseScene(filePath);

    auto* raytracer = new Raytracer();
    raytracer->initialize(scene);
    raytracer->render();
    raytracer->output();

    return 0;
}
