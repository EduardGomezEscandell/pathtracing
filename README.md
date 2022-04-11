### Pathtracing
C++ implementation of a pathtracing algorithm. Currently the project is in a very early stage, and the main file is only a "Hello, world!".
The goal of this project is to be in my portfolio. It demonstates my ability to prgram in C++ with CMake, and to test it with Doctest and github's CI tools.

### Building and running
First clone this repository and its dependencies (Eigen for the algebra and Doctest for the unit tests):
```bash
git clone git@github.com:EduardGomezEscandell/pathtracing.git
git submodule update --init
```
If you are on Linux, use:
```bash
bash configure.sh
```
If you are on Windows, use:
```powershell
.\configure.bat
```

The executable will be generated and a couple of symliks will be created:
```
bin
└── Release
    ├── pathtracer[.exe]
    └── run_tests[.exe]
```
The first one runs the program, the second one runs the tests. To compile in release mode,
define environment variable `BUILD_TYPE` to `Debug` before compiling, and the binaries will
be located at `bin/Debug/`.
