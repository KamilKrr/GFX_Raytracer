#include <iostream>
#include <vector>

#include "src/Image.h"
#include "src/SceneParser.h"
#include "src/ImageExporter.h"

int main() {

    auto* scene = SceneParser::parseScene("../scenes/example1.xml");
    auto* image = new Image( scene->getOutputFile(), scene->getCamera()->getResolutionHorizontal(), scene->getCamera()->getResolutionVertical());

    // Generate a gradient from red to blue horizontally and from green to yellow vertically
    for (unsigned y = 0; y < image->getHeight(); ++y) {
        for (unsigned x = 0; x < image->getWidth(); ++x) {
            // Calculate the index for the current pixel
            unsigned index = y * image->getWidth() + x;

            image->setPixelColor(index, *scene->getBackgroundColor());
        }
    }

    ImageExporter::exportImage(*image);

    std::cout << "Colorful image created successfully." << std::endl;

    return 0;
}
