cmake_minimum_required ( VERSION 3.1.0...3.27.0 )
project(raytracer LANGUAGES CXX)

set ( CMAKE_CXX_STANDARD          17 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

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
        src/ImageEncoder.h
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
        src/Ray.h
        src/ParallelLight.h
        src/Intersection.h
        src/WavefrontParser.h
        src/Mesh.h
        src/Face.h
        src/PointLight.h
        src/ImageDecoder.h
        src/ColorMaterial.h
        src/TextureMaterial.h
        src/point2.h
)

message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/we 4265") # Class has virtual functions, but its non-trivial destructor is not virtual
    add_compile_options("/w3 5038") # Data member will be initialized after [other] data member
    add_compile_options("/we 5204") # Class has virtual functions, but its trivial destructor is not virtual
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wmaybe-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wsometimes-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
endif()

# Create the executable and link it with the libraries
add_executable(raytracer ${PROJECT_SOURCES} ${PUGIXML_SOURCES} ${LODEPNG_SOURCES})
