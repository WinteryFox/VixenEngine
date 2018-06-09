cmake_minimum_required(VERSION 3.0)
project(VixenEngine)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_directories(${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

add_executable(VixenEngine main.cpp)

include_directories(${GLFW_INCLUDE_DIRS})

target_link_libraries(VixenEngine glfw3 glew32 opengl32 gdi32)