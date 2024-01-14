#ifndef RAYTRACER_IMAGEEXPORTER_H
#define RAYTRACER_IMAGEEXPORTER_H

#include "Image.h"
#include <iostream>
#include "../lib/lodepng/lodepng.h"

class ImageExporter {
public:
    static void exportImage(const Image& image) {
        std::string filename = image.getName();
        unsigned error = lodepng::encode(filename, ImageExporter::createColorBuffer(image.getColors()), image.getWidth(), image.getHeight());

        if (error) {
            std::cerr << "Error " << error << ": " << lodepng_error_text(error) << std::endl;
        }
    }
private:
    static std::vector<unsigned char> createColorBuffer(const std::vector<Color>& colors) {
        std::vector<unsigned char> buffer(colors.size() * 4);

        unsigned int idx{0};
        for (const auto &color : colors) {
            buffer[idx + 0] = color.r();
            buffer[idx + 1] = color.g();
            buffer[idx + 2] = color.b();
            buffer[idx + 3] = 255;
            idx += 4;
        }

        return buffer;
    }
};

#endif //RAYTRACER_IMAGEEXPORTER_H
