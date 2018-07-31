cmake_minimum_required(VERSION 3.0)
project(VixenEngine)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

link_directories(${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

if (WIN32)
	find_package(OPENGL REQUIRED)
	link_libraries(${OPENGL_LIBRARIES})

	find_package(GLEW REQUIRED)
	include_directories(${GLEW_INCLUDE_DIR})
	link_libraries(${GLEW_LIBRARIES})
else()
	pkg_search_module(GLEW REQUIRED glew)
	include_directories(${GLEW_INCLUDE_DIR})
	link_libraries(${GLEW_LIBRARIES})

	pkg_search_module(GLFW REQUIRED glfw3)
	include_directories(${GLFW_INCLUDE_DIR})
	link_libraries(${GLFW_LIBRARIES})

	pkg_search_module(ASSIMP REQUIRED assimp)
	include_directories(${ASSIMP_INCLUDE_DIR})
	link_libraries(${ASSIMP_LIBRARIES})

	pkg_search_module(PNG REQUIRED libpng)
	include_directories(${PNG_INCLUDE_DIRS})
	link_libraries(${PNG_LIBRARIES})
endif()

link_libraries(assimp glfw png)

add_executable(VixenEngine src/main.cpp src/Window.cpp src/Window.h src/Camera.cpp src/Camera.h src/Shader.cpp src/Shader.h src/Phong.cpp src/Phong.h src/Mesh.cpp src/Mesh.h src/Render.cpp src/Render.h src/Entity.cpp src/Entity.h src/Loader.cpp src/Loader.h)