set(CONTRIB "${CMAKE_SOURCE_DIR}/engine/contrib")

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

set(ZLIB_INCLUDE_DIR "${ZLIB}" "${CMAKE_BINARY_DIR}/engine/contrib/zlib" CACHE PATH "")
set(ZLIB_LIBRARY zlib CACHE STRING "")

# ---- BUILD LIBPNG ----

set(LIBPNG "${CONTRIB}/libpng")

set(PNG_TESTS OFF CACHE BOOL "")
set(PNG_SHARED ON CACHE BOOL "")
set(PNG_STATIC OFF CACHE BOOL "")

add_subdirectory("${LIBPNG}")

set(PNG_PNG_INCLUDE_DIR "${LIBPNG}" "${CMAKE_BINARY_DIR}/engine/contrib/libpng" CACHE PATH "")
set(PNG_LIBRARY png CACHE STRING "")

# ---- BUILD FREETYPE ----

set(FREETYPE "${CONTRIB}/freetype")

set(FT_WITH_PNG ON CACHE BOOL "")
set(FT_WITH_ZLIB ON CACHE BOOL "")

add_subdirectory("${FREETYPE}")

# ---- BUILD ASSIMP ----

set(ASSIMP "${CONTRIB}/assimp")

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "")
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
set(ASSIMP_NO_EXPORT ON CACHE BOOL "")
set(ASSIMP_BUILD_COLLADA_IMPORTER ON CACHE BOOL "")

set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "")

add_subdirectory("${ASSIMP}")

# ---- BUILD ENGINE ----

add_library(engine SHARED Window.cpp Window.h Camera.cpp Camera.h shaders/Shader.cpp shaders/Shader.h shaders/Phong.h Mesh.cpp Mesh.h render/EntityRender.cpp render/EntityRender.h Entity.cpp Entity.h Loader.cpp Loader.h Light.cpp Light.h Player.cpp Player.h Model.cpp Model.h Chunk.h Material.h render/EntityRender.cpp render/EntityRender.h Generator.cpp Generator.h render/TerrainRender.cpp render/TerrainRender.h Image.h Texture.h shaders/Phong.cpp shaders/GuiShader.cpp shaders/GuiShader.h font/Font.cpp font/Font.h font/Text.cpp font/Text.h render/FontRender.cpp render/FontRender.h font/Character.h render/MasterRender.cpp render/MasterRender.h shapes/Shapes.h)

set_target_properties(engine PROPERTIES OUTPUT_NAME "engine")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_include_directories(engine PUBLIC ${LIBPNG} ${FREETYPE}/include ${CMAKE_BINARY_DIR}/engine/contrib/assimp/include ${ASSIMP}/include ${LIBPNG} ${GLEW}/include ${CMAKE_SOURCE_DIR}/engine/contrib/glm)

target_link_libraries(engine -static winpthread -dynamic)
target_link_libraries(engine png freetype assimp zlib glfw glew ${OPENGL_LIBRARIES})