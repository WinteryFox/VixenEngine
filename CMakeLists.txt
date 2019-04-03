cmake_minimum_required(VERSION 2.8)
project(VixenEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SKIP_INSTALL_ALL ON)

set(CONTRIB "${CMAKE_SOURCE_DIR}/contrib")

# ---- BUILD GLEW ----

set(GLEW "${CONTRIB}/glew")

add_subdirectory("${GLEW}/build/cmake")

# ---- BUILD GLFW ----

set(GLFW "${CONTRIB}/glfw")

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
set(BUILD_TESTING OFF CACHE BOOL "")
set(BUILD_UTILS OFF CACHE BOOL "")

add_subdirectory("${GLFW}")

# ---- BUILD ZLIB ----

set(ZLIB "${CONTRIB}/zlib")

add_subdirectory("${ZLIB}")

set(ZLIB_INCLUDE_DIR "${ZLIB}" "${CMAKE_BINARY_DIR}/contrib/zlib")
set(ZLIB_LIBRARY zlib)

# ---- BUILD LIBPNG ----

set(LIBPNG "${CONTRIB}/libpng")

set(PNG_TESTS OFF CACHE BOOL "")
set(PNG_SHARED ON CACHE BOOL "")
set(PNG_STATIC OFF CACHE BOOL "")

add_subdirectory("${LIBPNG}")

#set(PNG_PNG_INCLUDE_DIR "${LIBPNG}" "${CMAKE_BINARY_DIR}/contrib/libpng")
#set(PNG_LIBRARY png)

# ---- BUILD FREETYPE ----

set(FREETYPE "${CONTRIB}/freetype")

add_subdirectory("${FREETYPE}")

# ---- BUILD ASSIMP ----

set(ASSIMP "${CONTRIB}/assimp")

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "")
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
set(ASSIMP_NO_EXPORT ON CACHE BOOL "")

add_subdirectory("${ASSIMP}")

#---- BUILD ENGINE ----

add_executable(engine src/main.cpp src/Window.cpp src/Window.h src/Camera.cpp src/Camera.h src/shaders/Shader.cpp src/shaders/Shader.h src/shaders/Phong.h src/Mesh.cpp src/Mesh.h src/render/EntityRender.cpp src/render/EntityRender.h src/Entity.cpp src/Entity.h src/Loader.cpp src/Loader.h src/Light.cpp src/Light.h src/Player.cpp src/Player.h src/Model.cpp src/Model.h src/Chunk.h src/Material.h src/render/EntityRender.cpp src/render/EntityRender.h src/Generator.cpp src/Generator.h src/render/TerrainRender.cpp src/render/TerrainRender.h src/Image.h src/Texture.h src/shaders/Phong.cpp src/shaders/GuiShader.cpp src/shaders/GuiShader.h src/font/Font.cpp src/font/Font.h src/font/Text.cpp src/font/Text.h src/render/FontRender.cpp src/render/FontRender.h src/font/Character.h src/render/MasterRender.cpp src/render/MasterRender.h src/shapes/Shapes.h)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_include_directories(engine PUBLIC ${LIBPNG} ${FREETYPE}/include ${CMAKE_BINARY_DIR}/contrib/assimp/include ${ASSIMP}/include ${LIBPNG} ${GLEW}/include ${CMAKE_SOURCE_DIR}/contrib/glm)

target_link_libraries(engine -static winpthread -dynamic)
target_link_libraries(engine png freetype assimp zlib glfw glew ${OPENGL_LIBRARIES})

#---- BUILD EXECUTABLE ----

#add_executable(VixenEngine src/main.cpp)
#[[
if (WIN32)
	target_link_libraries(engine gdi32 user32 kernel32)
else (UNIX AND APPLE)
	target_link_libraries(engine)
endif ()
]]
