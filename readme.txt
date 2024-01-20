# claim
I have done all tasks for this assignment.

I have tested the files
    - example1.xml
    - example2.xml
    - example3.xml
and they seem to match the official solutions very closely

Task 1 can be tested by removing the surfaces node from the example1.xml file, that way you will receive the black image
Task2 - 5 can be tested with the example.xml files 1-3

# tested environments
CLion on Macos
CLion on Windows
Almighty

# How to run
(This works on Almighty)
in the folder, create a build directory

    mkdir build
    cd build

inside first run

    cmake ..

then

    make

then the program can be started with

    ./raytracer

after which you will be prompted to input the path to the scene.xml file you want to render

# additional and general remarks

- the code in the file vec3.h is almost entirely copied from the Ray Tracing in One Weekend tutorial
- the code for the hit method in Sphere.h (collision detection) is also taken from the Ray Tracing in One Weekend tutorial and only slightly tweaked
- other than that, I have not followed the tutorial because the slides from the tutorial were sufficient and easier to understand
- I have developed this project on an apple silicon chip and have run into many compilation issues when testing on almighty but I think it should now work fine

https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials/truelambertianreflection
