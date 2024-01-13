#include <iostream>
#include <vector>
#include "lib/lodepng/lodepng.h"

int main() {
    // Image dimensions
    unsigned width = 500;
    unsigned height = 500;

    // Create a vector to store the pixel data
    std::vector<unsigned char> image(width * height * 4, 0); // Each pixel has 4 channels (RGBA)

    // Generate a gradient from red to blue horizontally and from green to yellow vertically
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            // Calculate the index for the current pixel
            unsigned index = 4 * (y * width + x);

            // Set red component based on horizontal position
            image[index + 0] = static_cast<unsigned char>(255 * x / width);

            // Set green component based on vertical position
            image[index + 1] = static_cast<unsigned char>(255 * y / height);

            // Set blue component as a constant value
            image[index + 2] = 128;

            // Set alpha component to 255 (fully opaque)
            image[index + 3] = 255;
        }
    }

    // Encode the pixel data into a PNG file
    unsigned error = lodepng::encode("colorful_image.png", image, width, height);

    if (error) {
        std::cerr << "Error " << error << ": " << lodepng_error_text(error) << std::endl;
        return 1;
    }

    std::cout << "Colorful image created successfully." << std::endl;

    return 0;
}
