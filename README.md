# HachitMath
A 3D Math library for use in Hachit. Designed to work with DirectX and OpenGL.

[![Build Status](https://travis-ci.org/thirddegree/HatchitMath.svg?branch=master)](https://travis-ci.org/thirddegree/HatchitMath)

### Build instructions

Building is simple. You just need CMake and a C++ compiler

On Linux it's as simple as

```
mkdir build
cd build
cmake ..
make
```

On Windows you'll probably want to run the CMake GUI to make a Visual Studio
project

### Building tests

Building tests works best on Linux. Travis CI is used to automate tests whenever
you push to the repo.

The tests can be run manually with

```
mkdir build
cd build
cmake .. -DBUILD_TEST=TRUE
make
ctest -VV
```
