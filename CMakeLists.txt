cmake_minimum_required(VERSION 3.11)
project(VixenEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(VixenEngine src/main.cpp src/Window.cpp src/Window.h src/Camera.cpp src/Camera.h src/shaders/Shader.cpp src/shaders/Shader.h src/shaders/Phong.h src/Mesh.cpp src/Mesh.h src/render/EntityRender.cpp src/render/EntityRender.h src/Entity.cpp src/Entity.h src/Loader.cpp src/Loader.h src/Light.cpp src/Light.h src/Player.cpp src/Player.h src/Model.cpp src/Model.h src/Chunk.cpp src/Chunk.h src/Material.h src/render/EntityRender.cpp src/render/EntityRender.h src/Generator.cpp src/Generator.h src/render/TerrainRender.cpp src/render/TerrainRender.h src/Image.h src/Texture.h src/shaders/Phong.cpp src/shaders/GuiShader.cpp src/shaders/GuiShader.h src/font/Font.cpp src/font/Font.h src/font/Text.cpp src/font/Text.h src/render/FontRender.cpp src/render/FontRender.h src/font/Character.h src/render/MasterRender.cpp src/render/MasterRender.h)

set(OpenGL_GL_PREFERENCE GLVND)

target_link_directories(VixenEngine PUBLIC ${CMAKE_BINARY_DIR} bin/assimp bin/zlib bin/freetype2 bin/glew bin/glfw3 bin/libpng)
target_include_directories(VixenEngine PUBLIC include)

find_package(OpenGL REQUIRED)
target_link_libraries(VixenEngine ${OPENGL_LIBRARIES})
target_include_directories(VixenEngine PUBLIC ${OPENGL_INCLUDE_DIR})

if (WIN32)
	target_link_libraries(VixenEngine glew32 glfw3 png16 freetype z assimp gdi32 user32 kernel32)
elseif (UNIX)
	find_package(PkgConfig REQUIRED)

	pkg_search_module(GLEW REQUIRED glew)
	target_link_libraries(VixenEngine ${GLEW_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${GLFW_INCLUDE_DIR})

	pkg_search_module(GLFW REQUIRED glfw3)
	target_link_libraries(VixenEngine ${GLFW_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${GLFW_INCLUDE_DIR})
	
	pkg_search_module(ASSIMP REQUIRED assimp)
	target_link_libraries(VixenEngine ${ASSIMP_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${ASSIMP_INCLUDE_DIR})
	
	pkg_search_module(PNG REQUIRED libpng)
	target_link_libraries(VixenEngine ${PNG_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${PNG_INCLUDE_DIRS})

	pkg_search_module(FREETYPE REQUIRED freetype)
	target_link_libraries(VixenEngine ${FREETYPE_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${FREETYPE_INCLUDE_DIRS})

	pkg_search_module(LIBZ REQUIRED z)
	target_link_libraries(VixenEngine ${LIBZ_LIBRARIES})
	target_include_directories(VixenEngine PUBLIC ${LIBZ_INCLUDE_DIRS})
endif ()