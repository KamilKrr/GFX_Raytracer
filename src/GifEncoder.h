#ifndef RAYTRACER_GIFENCODER_H
#define RAYTRACER_GIFENCODER_H

#include "Image.h"
#include <iostream>
#include "../lib/gif-h/gif.h"

class GifEncoder {
public:
    static void exportGif(std::vector<Image> images, int delay = 10) {
        std::string filename = images.front().getName();
        unsigned int width = images.front().getWidth();
        unsigned int height = images.front().getHeight();

        GifWriter g;
        GifBegin(&g, filename.c_str(), width, height, delay);

        for(const auto& image : images) {
            GifWriteFrame(&g, GifEncoder::createColorBuffer(image).data(), width, height, delay);
        }

        GifEnd(&g);
    }
private:
    static std::vector<unsigned char> createColorBuffer(const Image& image) {
        std::vector<unsigned char> buffer(image.getColors().size() * 4);

        unsigned int idx{0};
        for (int y = image.getHeight() - 1; y >= 0; --y) {
            for (int x = 0; x < image.getWidth(); ++x) {
                const auto& color = image.getColor(x, y);
                buffer[idx + 0] = std::min(static_cast<int>(color.r() * 255), 255);
                buffer[idx + 1] = std::min(static_cast<int>(color.g() * 255), 255);
                buffer[idx + 2] = std::min(static_cast<int>(color.b() * 255), 255);
                buffer[idx + 3] = 255;
                idx += 4;
            }
        }

        return buffer;
    }
};

#endif //RAYTRACER_GIFENCODER_H
