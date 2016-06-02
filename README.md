# HachitMath

[![Build Status](https://travis-ci.org/thirddegree/HatchitMath.svg?branch=master)](https://travis-ci.org/thirddegree/HatchitMath)
[![Documentation](https://codedocs.xyz/thirddegree/HatchitMath.svg)](https://codedocs.xyz/thirddegree/HatchitMath/)
[![Join the chat at https://gitter.im/thirddegree/HatchitDiscussion](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/thirddegree/HatchitDiscussion)

A 3D Math library for use in Hachit. Designed to work with DirectX and OpenGL.

---

### Contributing

If you have an issue with Hatchit specific to math code put it on this repo.

If you would like to make a contribution please make a fork and submit a pull request.

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

### FAQ

Please consult the [Hatchit Wiki](https://github.com/thirddegree/Hatchit/wiki)
