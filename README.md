Greeny
=============

Greeny is a C++ Green threads and coroutines library

This is a complete rewrite of https://github.com/yigalirani/green_threads library.

**Advantages over original library**
* Multiple platforms are supported. Original library was hardly bound to MS VisualStudio on i386.
* Fully object-oriented design with no global variables - this allows using green threads in multithreaded programs. You may have multiple green thread sets (contexts) in multiple threads.
* Arbitrary callback types (functors, callable objects, etc.)
* Variable stack sizes - you may set allocated stack size for each green thread.
* next() function without "tid" parameter to get a posted value of any other thread.

**Motivation (same as in original library):**
* Write faster multithreaded programs by utilizing reduced context switch time.
* Write shorter and more elegant programs by using the yield functionality that is modeled after the python yield keyword and co-routines.

**Getting started:**
look at the very short [api](https://github.com/nifigase/greeny/blob/master/Greeny.hpp) and [example program](https://github.com/nifigase/greeny/blob/master/test.cpp)

**Future development:**
* Automatically grow stack sizes if stacks are nearly exhausted

**Requirements**
* C++11-compatible compiler
* boost libraries (Used: ptr_containers)

**Building**
Build test using CMake:
* mkdir build
* cd build
* cmake -DCMAKE_BUILD_TYPE=DEBUG ..
* make

**Platforms**
* GCC on AMD64
* GCC on i386
