cmake_minimum_required(VERSION 3.12)
project(VixenEngine)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

link_directories(${CMAKE_BINARY_DIR})

add_executable(VixenEngine src/main.cpp src/Window.cpp src/Window.h src/Camera.cpp src/Camera.h src/Shader.cpp src/Shader.h src/Phong.cpp src/Phong.h src/Mesh.cpp src/Mesh.h src/Render.cpp src/Render.h src/Entity.cpp src/Entity.h src/Loader.cpp src/Loader.h src/Light.cpp src/Light.h src/Player.cpp src/Player.h src/Model.cpp src/Model.h)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
target_link_libraries(VixenEngine ${OPENGL_LIBRARIES})
target_include_directories(VixenEngine PUBLIC ${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
target_link_libraries(VixenEngine ${GLEW_LIBRARIES})
target_include_directories(VixenEngine PUBLIC ${GLEW_INCLUDE_DIRS})

#find_package(Vulkan REQUIRED)
#target_link_libraries(VixenEngine ${Vulkan_LIBRARIES})
#target_include_directories(VixenEngine PUBLIC ${Vulkan_INCLUDE_DIRS})

if (WIN32)
	target_link_libraries(VixenEngine assimp glfw3 png)
else (UNIX)
	find_package(PkgConfig REQUIRED)

	pkg_search_module(GLFW REQUIRED glfw3)
	target_link_libraries(VixenEngine ${GLFW_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${GLFW_INCLUDE_DIR})

	pkg_search_module(ASSIMP REQUIRED assimp)
	target_link_libraries(VixenEngine ${ASSIMP_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${ASSIMP_INCLUDE_DIR})

	pkg_search_module(PNG REQUIRED libpng)
	target_link_libraries(VixenEngine ${PNG_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${PNG_INCLUDE_DIRS})
endif()