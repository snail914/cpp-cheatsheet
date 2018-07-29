# cmake tutorial/cheatsheet
This is a personal study note from the original tutorial: http://derekmolloy.ie/hello-world-introductions-to-cmake/

## make vs cmake
- make (or rather a Makefile) is a buildsystem, Ninja is also a buildsystem
- cmake is a generator of buildsystems. It can produce makefiles for Ninja, make, etc

## command
```bash
cmake [-G <generator-name>] <path-to-CMakeLists.txt>
make [-C <path-to-src>] [-j]
```

## examples
[example code](https://github.com/snail914/cmake-example)

### hello world
```cmake
# use the current version of CMake on your system
cmake_minumum_required(VERSION 3.10.2)

# project name
project (hello)

#build executable using src file
add_executable(main helloworld.cpp)
```

### include directories
```bash
kli:~/workspace/cmake-example/example2$ tree
.
├── CMakeLists.txt
├── include
│   └── person.h
└── src
    ├── main.cpp
    └── persopn.cpp
```

```cmake
cmake_minumum_required(VERSION 3.10.2)
project(person)

#Bring the headers, such as Student.h into the project
include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SRC src/main.cpp src/person.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SRC src/*cpp)

add_executable(main ${SRC})
```

### build shared library
Same C++ source code from above example

```cmake
cmake_minimum_required(VERSION 3.10.2)
project(person)
include_directories(include)
set(SRC src/person.cpp)

set(CMAKE_BUILD_TYPE Release)

#Generate the shared library from the sources
add_library(person SHARED ${SRC})

#Set library installation location -- i.e., /usr/lib
# Use "make install" to apply
install(TARGETS person DESTINATION ./)
```
```bash
ldd libperson.so
```

### build static library
Same C++ source code from above example
```cmake
cmake_minimum_required(VERSION 3.10.2)
project(person)
include_directories(include)
set(SRC src/person.cpp)

set(CMAKE_BUILD_TYPE Release)

#Generate the static library from the sources
add_library(person STATIC ${SRC})

#Set library installation location -- i.e., /usr/lib
# Use "make install" to apply
install(TARGETS person DESTINATION ./)
```
Only difference is `add_library(person STATIC ${SRC}) `

Determine the constituents of a static library using `ar` (archive):
```bash
ar -t libperson.a
persopn.cpp.o
```
Use the GNU `nm` command to list the symbols in object files and binaries.
In this case, the command lists the symbols in the person library and their types
(e.g., T is code, U is undefined, R is read-only data).

### use static/shared libraries
```bash
kli:~/workspace/cmake-example/example5$ tree
.
├── CMakeLists.txt
├── libperson_repo
│   ├── include
│   │   └── person.h
│   ├── libperson.a
│   └── libperson.so
└── main.cpp
```

```cmake
cmake_minimum_required(VERSION 2.8.9)
project (app)

#For the shared library:
set (LIBS libperson.so)
link_directories(libperson_repo)

#For the static library:
#set (LIBS libperson.a)
#link_directories(libperson_repo)

include_directories(libperson_repo/include)
add_executable(main main.cpp)
target_link_libraries(main ${LIBS})
```
