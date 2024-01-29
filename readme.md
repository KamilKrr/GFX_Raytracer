# claim
Required Tasks: I have done all required tasks for this assignment\
Effects: I have implemented the effects motion blur and animations\
Bonus: I have implemented antialiasing using supersampling

I have implemented the feedback and fixed the mistakes from my previous submission Lab 3a

I have tested these files and they should match the official solutions exactly

- example1.xml
- example2.xml
- example3.xml
- example4.xml
- example5.xml
- example6.xml
- example7.xml
- example8.xml
- example9.xml -> this takes quite some time to render (~5 minutes)

Additionally I provide the following scene files to test the effects and bonus (in the ./scenes/ directory):

- blur.xml -> renders 15 frames of two spheres moving in different directions with motion blur
- anim.xml -> renders a 30 frame gif of the camera position and lookat vectors being animated
- supersampling.xml -> renders example 4 with supersamling (3x3 = 9 samples per pixel)

All rendered images are in the ./renders/ directory

# tested environments
CLion on macOS, CLion on Windows, Almighty

# How to run
(This works on Almighty)
in the folder, create a build directory

    mkdir build
    cd build

inside the build directory run

    cmake ..

then

    make

then the program can be started with

    ./raytracer

after which you will be prompted to input the path to the scene.xml file you want to render

# additional and general remarks

- the code in the file vec3.h is almost entirely copied from the Ray Tracing in One Weekend tutorial
- the code for the hit method in Sphere.h (collision detection) is also taken from the Ray Tracing in One Weekend tutorial and only slightly tweaked
- the code for triangle intersection is taken entirely from scratchapixel
- the code for refraction is taken entirely from scratchapixel
- the rendered animation gif often shows some weird shadow glitches.
    I tried rendering the frames once and exporting both GIF and PNG images.
    The GIF always had some glitches while the PNG did not, so I assume the GIF library or compression is at fault here.

If I were to add something to the tutorial slides regarding object transformations it would be:\
"don't forget to transform the shadow rays as well"

# sources
- https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials/truelambertianreflection
- https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection.html
- https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel.html
