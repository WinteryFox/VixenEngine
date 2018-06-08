cmake_minimum_required(VERSION 3.0)
project(VixenEngine)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

add_executable(VixenEngine main.cpp)