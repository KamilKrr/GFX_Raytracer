#ifndef RAYTRACER_IMAGEEXPORTER_H
#define RAYTRACER_IMAGEEXPORTER_H

#include "Image.h"
#include <iostream>
#include "../lib/lodepng/lodepng.h"

class ImageExporter {
public:
    static void exportImage(const Image& image) {
        std::string filename = image.getName();
        unsigned error = lodepng::encode(filename, ImageExporter::createColorBuffer(image), image.getWidth(), image.getHeight());

        if (error) {
            std::cerr << "Error " << error << ": " << lodepng_error_text(error) << std::endl;
        }
    }
private:
    static std::vector<unsigned char> createColorBuffer(const Image& image) {
        std::vector<unsigned char> buffer(image.getColors().size() * 4);

        unsigned int idx{0};
        for (int y = image.getHeight() - 1; y >= 0; --y) {
            for (int x = 0; x < image.getWidth(); ++x) {
                const auto& color = image.getColor(x, y);
                buffer[idx + 0] = std::min(static_cast<int>(color.r()), 255);
                buffer[idx + 1] = std::min(static_cast<int>(color.g()), 255);
                buffer[idx + 2] = std::min(static_cast<int>(color.b()), 255);
                buffer[idx + 3] = 255;
                idx += 4;
            }
        }

        return buffer;
    }
};

#endif //RAYTRACER_IMAGEEXPORTER_H
