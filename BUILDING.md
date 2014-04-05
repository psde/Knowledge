Building Knowledge
===================

Basics
------

Knowledge uses [CMake](http://cmake.org/) (>=2.8.12) to build the project. A compiler with C++11 support is needed (Visual Studio 2013 or a recent version of either gcc or clang).

Dependencies
-------------

Knowledge depends on several thirdparty libraries:
* Qt >=4.8.6 (4.8.5 can be used, but a Patch is needed for Visual Studio 2013 support)
* OpenCV >=2.4.8

Building Knowledge
-------------------

The following steps should help you (re)build Knowledge from the command line.

1. Make sure you have all dependencies installed and compiled somewhere on your system.
2. Checkout the source somewhere on your filesystem with 

        git clone https://github.com/psde/Knowledge.git

3. If you installed some or all dependencies in unusual places, create a `UserUserDefinitions.cmake` and set the correct paths for all dependencies. You can use the `UserUserDefinitions.cmake.example` file as a start by copying it.
4. Create a `build` folder which cmake will use to build Knowledge
5. Open a terminal, `cd` into the folder created in step 4 and call `cmake ..`.

CMake is now building a platform-specific build system. On Windows, you can now open the Visual Studio solution file with Visual Studio 2013. On Linux/Mac OS X you can build the project with `make`.