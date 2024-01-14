#include <iostream>
#include <vector>

#include "src/Raytracer.h"
#include "src/Image.h"
#include "src/SceneParser.h"
#include "src/ImageExporter.h"

int main() {

    auto* scene = SceneParser::parseScene("../scenes/example1.xml");

    auto* raytracer = new Raytracer();
    raytracer->initialize(scene);
    raytracer->render();
    raytracer->output();

    return 0;
}
