cmake_minimum_required(VERSION 3.0)
project(VixenEngine)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(PkgConfig REQUIRED)

link_directories(${CMAKE_BINARY_DIR})

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OPENGL REQUIRED)
link_libraries(${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
link_libraries(${GLEW_LIBRARIES})

link_libraries(assimp glfw glew png)

add_executable(VixenEngine src/main.cpp src/Window.cpp src/Window.h src/Camera.cpp src/Camera.h src/Shader.cpp src/Shader.h src/Phong.cpp src/Phong.h src/Mesh.cpp src/Mesh.h src/Render.cpp src/Render.h src/Entity.cpp src/Entity.h src/Loader.cpp src/Loader.h)