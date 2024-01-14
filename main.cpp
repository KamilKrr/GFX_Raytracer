#include <iostream>
#include <vector>

#include "src/Raytracer.h"
#include "src/SceneParser.h"

int main() {

    auto* scene = SceneParser::parseScene("../scenes/example3.xml");

    auto* raytracer = new Raytracer();
    raytracer->initialize(scene);
    raytracer->render();
    raytracer->output();

    return 0;
}
