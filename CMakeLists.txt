cmake_minimum_required(VERSION 3.8)
project(VixenEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif ()

set(SKIP_INSTALL_ALL ON)

option(VIXEN_BUILD_TEST "Build the engine test executable" ON)

#---- BUILD ENGINE ----

add_subdirectory(engine/)

#---- BUILD TEST ----

if (VIXEN_BUILD_TEST)
    add_subdirectory(test/)
endif(VIXEN_BUILD_TEST)