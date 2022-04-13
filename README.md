### Pathtracing
C++ implementation of a pathtracing algorithm. Currently the project is in its early stages.
The goal of this project is to play around with various technologies I am interested in. Particularly using C++ with CMake, and to test it with Doctest and github's CI tools.

## Status
The general structure of the program works, but there are some critical enchancements to make:
- More materials (currently all materials are non-reflective emitters)
  - Reflection
  - Transparency?
  - Refraction?
- More geometries:
  - Triangles, in order to use meshes
- Easier imports
  - To import meshes
- Cleaner output
  - Currently using bitmaps, should use some library to convert to png or jpeg.

### Building and running
First clone this repository and its dependencies (Eigen for the algebra and Doctest for the unit tests):
```bash
git clone git@github.com:EduardGomezEscandell/pathtracing.git
git submodule update --init
```
Then build:
```bash
bash configure.sh
```

The executable will be generated and a couple of symlinks will be created:
```
bin
└── Release
    ├── demo_three_balls
    └── run_tests
```
The first one runs a demo, the second one runs the tests. To compile in debug mode,
define environment variable `BUILD_TYPE` to `Debug` before compiling, and the binaries will
be located at `bin/Debug/`.

The demo will create `demo_three_balls.ppm`, a raw binary format. I open them with a VSCode extension. Alternatively, you can 
install NetBPM tools (`sudo apt install netbpm`) and use `pnmtopng demo_three_balls.ppm > demo_three_balls.png` to convert to png.

### Results
Since the project is in an early stage, the results are not very impressive:

![demo_three_balls](https://user-images.githubusercontent.com/47142856/163073427-2e6640a4-4340-4962-9858-b625d849f78c.png)

As more features are implemented, more interesting demos will be added.
