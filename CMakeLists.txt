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

add_executable(VixenEngine src/main.cpp src/Window.cpp src/Window.h src/Camera.cpp src/Camera.h src/Shader.cpp src/Shader.h src/Phong.cpp src/Phong.h src/Mesh.cpp src/Mesh.h src/Render.cpp src/Render.h src/Entity.cpp src/Entity.h src/Loader.cpp src/Loader.h)

include_directories(${GLFW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})

target_link_libraries(VixenEngine assimp glfw3 glew32 opengl32 gdi32)