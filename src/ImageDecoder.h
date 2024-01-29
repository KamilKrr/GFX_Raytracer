#ifndef RAYTRACER_IMAGEDECODER_H
#define RAYTRACER_IMAGEDECODER_H


#include <string>
#include "Image.h"
#include "../lib/lodepng/lodepng.h"

class ImageDecoder {
public:
    static Image importImage(const std::string& filename) {
        std::vector<unsigned char> buffer;
        unsigned int width, height;

        unsigned error = lodepng::decode(buffer, width, height, filename);

        if(error) std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

        Image image{filename, width, height};

        unsigned int idx{0};
        for (unsigned int i = 0; i < buffer.size(); i+=4, ++idx) {
            const auto& color = Color(
                    buffer.at(i+0)/255.0,
                    buffer.at(i+1)/255.0,
                    buffer.at(i+2)/255.0
                    );
            image.setPixelColor(idx, color);
        }
        return image;
    }
};
#endif //RAYTRACER_IMAGEDECODER_H
