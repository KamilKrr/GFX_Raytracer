#include <iostream>
#include <vector>

#include "src/Image.h"
#include "src/ImageExporter.h"

int main() {

    auto* image = new Image( "export", 500, 500);

    // Generate a gradient from red to blue horizontally and from green to yellow vertically
    for (unsigned y = 0; y < image->getHeight(); ++y) {
        for (unsigned x = 0; x < image->getWidth(); ++x) {
            // Calculate the index for the current pixel
            unsigned index = y * image->getWidth() + x;

            auto* color = new Color(
                    static_cast<unsigned char>(255 * x / image->getWidth()),
                    static_cast<unsigned char>(255 * y / image->getHeight()),
                    128
                );

            image->setPixelColor(index, *color);
        }
    }

    ImageExporter::exportImage(*image);

    std::cout << "Colorful image created successfully." << std::endl;

    return 0;
}
