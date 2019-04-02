cmake_minimum_required(VERSION 3.11)
project(VixenEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED=ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static-libstdc++ -static-libgcc")
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CONTRIB ${CMAKE_SOURCE_DIR}/contrib)

# ---- BUILD GLEW ----

set(GLEW ${CONTRIB}/glew)

add_subdirectory(${GLEW}/build/cmake)

# ---- BUILD GLFW ----

set(GLFW ${CONTRIB}/glfw)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(${GLFW})

# ---- BUILD ZLIB ----

set(ZLIB ${CONTRIB}/zlib)

add_subdirectory(${ZLIB})

set(ZLIB_INCLUDE_DIR ${ZLIB} ${CMAKE_BINARY_DIR}/contrib/zlib)
set(ZLIB_LIBRARY zlib)

# ---- BUILD LIBPNG ----

set(LIBPNG ${CONTRIB}/libpng)

add_subdirectory(${LIBPNG})

# ---- BUILD FREETYPE ----

set(FREETYPE ${CONTRIB}/freetype)

add_subdirectory(${FREETYPE})

# ---- BUILD ASSIMP ----

set(ASSIMP ${CONTRIB}/assimp)

add_subdirectory(${ASSIMP})

#---- BUILD ENGINE ----

add_library(ENGINE src/Window.cpp src/Window.h src/Camera.cpp src/Camera.h src/shaders/Shader.cpp src/shaders/Shader.h src/shaders/Phong.h src/Mesh.cpp src/Mesh.h src/render/EntityRender.cpp src/render/EntityRender.h src/Entity.cpp src/Entity.h src/Loader.cpp src/Loader.h src/Light.cpp src/Light.h src/Player.cpp src/Player.h src/Model.cpp src/Model.h src/Chunk.h src/Material.h src/render/EntityRender.cpp src/render/EntityRender.h src/Generator.cpp src/Generator.h src/render/TerrainRender.cpp src/render/TerrainRender.h src/Image.h src/Texture.h src/shaders/Phong.cpp src/shaders/GuiShader.cpp src/shaders/GuiShader.h src/font/Font.cpp src/font/Font.h src/font/Text.cpp src/font/Text.h src/render/FontRender.cpp src/render/FontRender.h src/font/Character.h src/render/MasterRender.cpp src/render/MasterRender.h src/shapes/Shapes.h)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
target_include_directories(ENGINE PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(ENGINE -static winpthread -dynamic)
target_link_libraries(ENGINE png freetype assimp zlib glfw glew ${OPENGL_LIBRARIES})

#---- BUILD EXECUTABLE ----

add_executable(VixenEngine src/main.cpp)

if (WIN32)
	target_link_libraries(VixenEngine ENGINE gdi32 user32 kernel32)
else (UNIX AND APPLE)
	target_link_libraries(VixenEngine ENGINE)
endif ()