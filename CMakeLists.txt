cmake_minimum_required(VERSION 3.27)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

# Add source files for pugixml
set(PUGIXML_SOURCE_DIR lib/pugixml)
set(PUGIXML_SOURCES
        ${PUGIXML_SOURCE_DIR}/pugixml.cpp
)

# Add source files for lodepng
set(LODEPNG_SOURCE_DIR lib/lodepng)
set(LODEPNG_SOURCES
        ${LODEPNG_SOURCE_DIR}/lodepng.cpp
)

# Add source files for your project
set(PROJECT_SOURCES
        src/vec3.h
        src/Raytracer.h
        src/ImageExporter.h
        src/Image.h
        src/Color.h
        src/Scene.h
        src/Camera.h
        src/Light.h
        src/AmbientLight.h
        src/Surface.h
        src/Sphere.h
        src/SceneParser.h
        main.cpp
        src/Material.h
)

# Create the executable and link it with the libraries
add_executable(raytracer ${PROJECT_SOURCES} ${PUGIXML_SOURCES} ${LODEPNG_SOURCES})
