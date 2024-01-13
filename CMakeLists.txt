cmake_minimum_required(VERSION 3.27)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

# Add LodePNG library to the project
add_library(lodepng lib/lodepng/lodepng.cpp
        src/vec3.h
        src/Raytracer.h
        src/ImageExporter.h
        src/Image.h
        src/Color.h)

# Create the executable and link it with the LodePNG library
add_executable(raytracer main.cpp)
target_link_libraries(raytracer PRIVATE lodepng)
