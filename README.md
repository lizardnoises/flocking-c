# boids

A simple boid flocking behavior simulator

## Prerequisites

- [CMake](https://cmake.org/)
- One of the native [build tools](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) supported by CMake

## Building

Clone the repository and submodules

```
git clone --recursive https://github.com/moorsean/boids.git
cd boids
```

If already cloned without the submodule, fetch it with

```
git submodule init
git submodule update
```

And build out-of-source

```
mkdir -p build
cd build
cmake [-G <generator>] ..
cmake --build .
```

`<generator>` can be any of CMake's [generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) matching an available build system.

Example for Visual Studio 16:

```
cmake -G "Visual Studio 16 2019" ..
```

Example for MinGW:

```
cmake -G "MinGW Makefiles" ..
```

Example for Ninja:

```
cmake -G "Ninja" ..
```

After building, execute the program `boid`, located in the build target's directory.

Example for Visual Studio:

```
cd Debug
./boids
```

Example for MinGW/Ninja:

```
./boids
```

## Built with

- [raylib](https://www.raylib.com/) - graphics library
- [GLFW](https://www.glfw.org/) - OpenGL and window library

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details