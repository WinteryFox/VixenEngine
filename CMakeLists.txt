cmake_minimum_required(VERSION 3.11)
project(VixenEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED=ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static-libstdc++ -static-libgcc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# ---- BUILD GLEW ----

if (NOT UNIX)
	set(GLEW ${CMAKE_SOURCE_DIR}/contrib/glew)
	set(GLEW_SRC
			${GLEW}/src/glew.c
			${GLEW}/include/GL/glew.h
			${GLEW}/include/GL/wglew.h
			${GLEW}/include/GL/glxew.h)

	add_definitions(-DGLEW_STATIC)

	add_library(glew STATIC ${GLEW_SRC})
	target_include_directories(glew PUBLIC ${GLEW}/include)
endif()

# ---- BUILD GLFW ----

set(GLFW ${CMAKE_SOURCE_DIR}/contrib/glfw)

if(WIN32)
	add_definitions(-D_GLFW_WIN32)
elseif(UNIX AND NOT APPLE)
	add_definitions(-D_GLFW_WAYLAND)
elseif(UNIX AND APPLE)
	add_definitions(-D_GLFW_COCOA)
endif()

set(GLFW_SRC
		${GLFW}/src/context.c
		${GLFW}/src/init.c
		${GLFW}/src/input.c
		${GLFW}/src/monitor.c
		${GLFW}/src/vulkan.c
		${GLFW}/src/window.c)
set (GLFW_HEADERS
		${GLFW}/src/glfw_config.h
		${GLFW}/include/GLFW/glfw3.h
		${GLFW}/include/GLFW/glfw3native.h)

if (WIN32)
	list(APPEND GLFW_SRC
			${GLFW}/src/win32_init.c
			${GLFW}/src/win32_joystick.c
			${GLFW}/src/win32_monitor.c
			${GLFW}/src/win32_time.c
			${GLFW}/src/win32_tls.c
			${GLFW}/src/win32_window.c
			${GLFW}/src/wgl_context.c
			${GLFW}/src/egl_context.c)
	list(APPEND GLFW_HEADERS
			${GLFW}/src/win32_platform.h
			${GLFW}/src/win32_joystick.h
			${GLFW}/src/win32_platform.h
			${GLFW}/src/wgl_context.h
			${GLFW}/src/egl_context.h)
elseif (UNIX AND APPLE)
	list(APPEND GLFW_SRC
			${GLFW}/src/cocoa_init.m
			${GLFW}/src/cocoa_joystick.m
			${GLFW}/src/cocoa_monitor.m
			${GLFW}/src/cocoa_window.m
			${GLFW}/src/cocoa_time.c
			${GLFW}/src/posix_tls.c
			${GLFW}/src/nsgl_context.m)
	LIST(APPEND GLFW_HEADERS
			${GLFW}/src/cocoa_platform.h
			${GLFW}/src/cocoa_joystick.h
			${GLFW}/src/posix_tls.h
			${GLFW}/src/nsgl_context)

	set_source_files_properties(${GLFW_SRC} PROPERTIES LANGUAGE C)

	find_library(COCOA_FRAMEWORK Cocoa)
	find_library(IOKIT_FRAMEWORK IOKit)
	find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
	find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
	mark_as_advanced(COCOA_FRAMEWORK
			IOKIT_FRAMEWORK
			CORE_FOUNDATION_FRAMEWORK
			CORE_VIDEO_FRAMEWORK)
	list(APPEND GLFW_LIBS "${COCOA_FRAMEWORK}"
			"${IOKIT_FRAMEWORK}"
			"${CORE_FOUNDATION_FRAMEWORK}"
			"${CORE_VIDEO_FRAMEWORK}")
elseif (UNIX)
	error()
endif()

add_library(glfw STATIC ${GLFW_SRC} ${GLFW_HEADER})
target_compile_definitions(glfw PRIVATE "$<$<BOOL:${MINGW}>:UNICODE;WINVER=0x0501>")
target_link_libraries(glfw INTERFACE ${GLFW_LIBS})

# ---- BUILD ZLIB ----

set(ZLIB ${CMAKE_SOURCE_DIR}/contrib/zlib)
set(ZLIB_SRC
		${ZLIB}/zconf.h
		${ZLIB}/zlib.h
		${ZLIB}/crc32.h
		${ZLIB}/deflate.h
		${ZLIB}/gzguts.h
		${ZLIB}/inffast.h
		${ZLIB}/inffixed.h
		${ZLIB}/inflate.h
		${ZLIB}/inftrees.h
		${ZLIB}/trees.h
		${ZLIB}/zutil.h
		${ZLIB}/adler32.c
		${ZLIB}/compress.c
		${ZLIB}/crc32.c
		${ZLIB}/deflate.c
		${ZLIB}/gzclose.c
		${ZLIB}/gzlib.c
		${ZLIB}/gzread.c
		${ZLIB}/gzwrite.c
		${ZLIB}/inflate.c
		${ZLIB}/infback.c
		${ZLIB}/inftrees.c
		${ZLIB}/inffast.c
		${ZLIB}/trees.c
		${ZLIB}/uncompr.c
		${ZLIB}/zutil.c)

add_library(zlib STATIC ${ZLIB_SRC})
set_target_properties(zlib PROPERTIES LIBRARY_OUTPUT_NAME z1)

# ---- BUILD LIBPNG ----

set(LIBPNG ${CMAKE_SOURCE_DIR}/contrib/libpng)

configure_file(${LIBPNG}/scripts/pnglibconf.h.prebuilt ${LIBPNG}/pnglibconf.h)

set(LIBPNG_SRC
		${LIBPNG}/png.c
		${LIBPNG}/pngerror.c
		${LIBPNG}/pngget.c
		${LIBPNG}/pngmem.c
		${LIBPNG}/pngpread.c
		${LIBPNG}/pngread.c
		${LIBPNG}/pngrio.c
		${LIBPNG}/pngrtran.c
		${LIBPNG}/pngrutil.c
		${LIBPNG}/pngset.c
		${LIBPNG}/pngtrans.c
		${LIBPNG}/pngwio.c
		${LIBPNG}/pngwrite.c
		${LIBPNG}/pngwtran.c
		${LIBPNG}/pngwutil.c)

add_library(png STATIC ${LIBPNG_SRC})
target_link_directories(png PUBLIC ${LIBPNG})

# ---- BUILD FREETYPE ----

set(FREETYPE ${CMAKE_SOURCE_DIR}/contrib/freetype)

file(GLOB FREETYPE_PUBLIC_HEADERS ${FREETYPE}/include/ft2build.h ${FREETYPE}/include/freetype/*.h)
file(GLOB FREETYPE_PUBLIC_CONFIG_HEADERS ${FREETYPE}/include/freetype/config/*.h)
file(GLOB FREETYPE_PRIVATE_HEADERS ${FREETYPE}/include/freetype/internal/*.h)

set(FREETYPE_SRC
		${FREETYPE}/src/autofit/autofit.c
		${FREETYPE}/src/base/ftbase.c
		${FREETYPE}/src/base/ftbbox.c
		${FREETYPE}/src/base/ftbdf.c
		${FREETYPE}/src/base/ftbitmap.c
		${FREETYPE}/src/base/ftcid.c
		${FREETYPE}/src/base/ftfstype.c
		${FREETYPE}/src/base/ftgasp.c
		${FREETYPE}/src/base/ftglyph.c
		${FREETYPE}/src/base/ftgxval.c
		${FREETYPE}/src/base/ftinit.c
		${FREETYPE}/src/base/ftmm.c
		${FREETYPE}/src/base/ftotval.c
		${FREETYPE}/src/base/ftpatent.c
		${FREETYPE}/src/base/ftpfr.c
		${FREETYPE}/src/base/ftstroke.c
		${FREETYPE}/src/base/ftsynth.c
		${FREETYPE}/src/base/ftsystem.c
		${FREETYPE}/src/base/fttype1.c
		${FREETYPE}/src/base/ftwinfnt.c
		${FREETYPE}/src/bdf/bdf.c
		${FREETYPE}/src/bzip2/ftbzip2.c
		${FREETYPE}/src/cache/ftcache.c
		${FREETYPE}/src/cff/cff.c
		${FREETYPE}/src/cid/type1cid.c
		${FREETYPE}/src/gzip/ftgzip.c
		${FREETYPE}/src/lzw/ftlzw.c
		${FREETYPE}/src/pcf/pcf.c
		${FREETYPE}/src/pfr/pfr.c
		${FREETYPE}/src/psaux/psaux.c
		${FREETYPE}/src/pshinter/pshinter.c
		${FREETYPE}/src/psnames/psnames.c
		${FREETYPE}/src/raster/raster.c
		${FREETYPE}/src/sfnt/sfnt.c
		${FREETYPE}/src/smooth/smooth.c
		${FREETYPE}/src/truetype/truetype.c
		${FREETYPE}/src/type1/type1.c
		${FREETYPE}/src/type42/type42.c
		${FREETYPE}/src/winfonts/winfnt.c)

if (WIN32)
	enable_language(RC)
	list(APPEND FREETYPE_SRC ${FREETYPE}/builds/windows/ftdebug.c
			${FREETYPE}/src/base/ftver.rc)
elseif (WINCE)
	list(APPEND FREETYPE_SRC ${FREETYPE}/builds/wince/ftdebug.c)
else ()
	list(APPEND FREETYPE_SRC ${FREETYPE}/src/base/ftdebug.c)
endif ()

add_library(freetype ${FREETYPE_PUBLIC_HEADERS} ${FREETYPE_PUBLIC_CONFIG_HEADERS} ${FREETYPE_PRIVATE_HEADERS} ${FREETYPE_SRC})
target_compile_definitions(freetype PRIVATE FT2_BUILD_LIBRARY)
target_include_directories(freetype PRIVATE ${FREETYPE}/include)

# ---- BUILD IRRXML ----

set(IRRXML ${CMAKE_SOURCE_DIR}/contrib/irrxml/src)
set(IRRXML_SRC
		${IRRXML}/CXMLReaderImpl.h
		${IRRXML}/heapsort.h
		${IRRXML}/irrArray.h
		${IRRXML}/irrString.h
		${IRRXML}/irrTypes.h
		${IRRXML}/irrXML.cpp
		${IRRXML}/irrXML.h)

add_library(irrxml STATIC ${IRRXML_SRC})
set_target_properties(irrxml PROPERTIES LIBRARY_OUTPUT_NAME irrxml)

# ---- BUILD ASSIMP ----

set(ASSIMP ${CMAKE_SOURCE_DIR}/contrib/assimp)
set(ASSIMP_BIN ${CMAKE_SOURCE_DIR}/contrib/assimp/code)

add_definitions(-DASSIMP_BUILD_NO_X_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_OBJ_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_AMF_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_3DS_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_MD3_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_MD2_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_PLY_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_MDL_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_ASE_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_3DS_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_HMP_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_SMD_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_MDC_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_MD5_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_STL_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_LWO_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_DXF_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_NFF_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_RAW_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_SIB_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_OFF_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_AC_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_BVH_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_IRRMESH_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_IRR_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_Q3D_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_B3D_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_TERRAGEN_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_CSM_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_3D_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_LWS_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_OGRE_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_OPENGEX_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_MS3D_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_COB_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_BLEND_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_Q3BSP_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_NDO_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_IFC_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_XGL_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_FBX_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_ASSBIN_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_GLTF_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_C4D_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_3MF_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_X3D_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_NO_MMD_IMPORTER=ON)
add_definitions(-DASSIMP_BUILD_ASSIMP_TOOLS=OFF)
add_definitions(-DASSIMP_BUILD_SAMPLES=OFF)
add_definitions(-DASSIMP_BUILD_TESTS=OFF)
add_definitions(-DASSIMP_BUILD_ZLIB=OFF)
add_definitions(-DSYSTEM_IRRXML=ON)

configure_file(${ASSIMP}/revision.h.in ${ASSIMP}/include/assimp/revision.h)
configure_file(${ASSIMP}/include/assimp/config.h.in ${ASSIMP}/include/assimp/assimp/config.h)

add_library(assimp STATIC
		${ASSIMP}/include/assimp/assimp/config.h
		${ASSIMP}/include/assimp/revision.h
		${ASSIMP}/include/assimp/version.h
		${ASSIMP_BIN}/revision.h
		${ASSIMP_BIN}/Version.cpp
		${ASSIMP_BIN}/Importer.cpp
		${ASSIMP_BIN}/Importer.h
		${ASSIMP_BIN}/scene.cpp
		${ASSIMP_BIN}/ColladaParser.cpp
		${ASSIMP_BIN}/ColladaParser.h
		${ASSIMP_BIN}/ColladaLoader.cpp
		${ASSIMP_BIN}/ColladaLoader.h
		${ASSIMP_BIN}/irrXMLWrapper.h
		${ASSIMP_BIN}/MaterialSystem.cpp
		${ASSIMP_BIN}/MaterialSystem.h
		${ASSIMP_BIN}/Assimp.cpp
		${ASSIMP_BIN}/DefaultIOSystem.cpp
		${ASSIMP_BIN}/DefaultIOStream.cpp
		${ASSIMP_BIN}/DefaultLogger.cpp
		${ASSIMP_BIN}/BaseImporter.cpp
		${ASSIMP_BIN}/DefaultProgressHandler.h
		${ASSIMP_BIN}/ImporterRegistry.cpp
		${ASSIMP_BIN}/PostStepRegistry.cpp
		${ASSIMP_BIN}/ValidateDataStructure.h
		${ASSIMP_BIN}/ValidateDataStructure.cpp
		${ASSIMP_BIN}/BaseProcess.h
		${ASSIMP_BIN}/BaseProcess.cpp
		${ASSIMP_BIN}/PretransformVertices.h
		${ASSIMP_BIN}/PretransformVertices.cpp
		${ASSIMP_BIN}/ProcessHelper.cpp
		${ASSIMP_BIN}/ProcessHelper.h
		${ASSIMP_BIN}/ConvertToLHProcess.cpp
		${ASSIMP_BIN}/ConvertToLHProcess.h
		${ASSIMP_BIN}/SpatialSort.cpp
		${ASSIMP_BIN}/SpatialSort.h
		${ASSIMP_BIN}/DeboneProcess.cpp
		${ASSIMP_BIN}/DeboneProcess.h
		${ASSIMP_BIN}/SplitLargeMeshes.cpp
		${ASSIMP_BIN}/SplitLargeMeshes.h
		${ASSIMP_BIN}/ImproveCacheLocality.cpp
		${ASSIMP_BIN}/ImproveCacheLocality.h
		${ASSIMP_BIN}/VertexTriangleAdjacency.cpp
		${ASSIMP_BIN}/VertexTriangleAdjacency.h
		${ASSIMP_BIN}/SceneCombiner.cpp
		${ASSIMP_BIN}/LimitBoneWeightsProcess.cpp
		${ASSIMP_BIN}/ScenePreprocessor.cpp
		${ASSIMP_BIN}/ScenePreprocessor.h
		${ASSIMP_BIN}/CalcTangentsProcess.cpp
		${ASSIMP_BIN}/CalcTangentsProcess.h
		${ASSIMP_BIN}/JoinVerticesProcess.cpp
		${ASSIMP_BIN}/JoinVerticesProcess.h
		${ASSIMP_BIN}/GenVertexNormalsProcess.cpp
		${ASSIMP_BIN}/GenVertexNormalsProcess.h
		${ASSIMP_BIN}/GenFaceNormalsProcess.cpp
		${ASSIMP_BIN}/GenFaceNormalsProcess.h
		${ASSIMP_BIN}/SplitByBoneCountProcess.cpp
		${ASSIMP_BIN}/SplitByBoneCountProcess.h
		${ASSIMP_BIN}/FixNormalsStep.cpp
		${ASSIMP_BIN}/FixNormalsStep.h
		${ASSIMP_BIN}/OptimizeMeshes.cpp
		${ASSIMP_BIN}/OptimizeMeshes.h
		${ASSIMP_BIN}/FindInvalidDataProcess.cpp
		${ASSIMP_BIN}/FindInvalidDataProcess.h
		${ASSIMP_BIN}/SortByPTypeProcess.cpp
		${ASSIMP_BIN}/SortByPTypeProcess.h
		${ASSIMP_BIN}/TriangulateProcess.cpp
		${ASSIMP_BIN}/TriangulateProcess.h
		${ASSIMP_BIN}/TextureTransform.cpp
		${ASSIMP_BIN}/TextureTransform.h
		${ASSIMP_BIN}/ComputeUVMappingProcess.cpp
		${ASSIMP_BIN}/ComputeUVMappingProcess.h
		${ASSIMP_BIN}/FindDegenerates.cpp
		${ASSIMP_BIN}/FindDegenerates.h
		${ASSIMP_BIN}/RemoveVCProcess.cpp
		${ASSIMP_BIN}/RemoveVCProcess.h
		${ASSIMP_BIN}/RemoveRedundantMaterials.cpp
		${ASSIMP_BIN}/RemoveRedundantMaterials.h
		${ASSIMP_BIN}/FindInstancesProcess.cpp
		${ASSIMP_BIN}/FindInstancesProcess.h
		${ASSIMP_BIN}/OptimizeGraph.cpp
		${ASSIMP_BIN}/OptimizeGraph.h
		${ASSIMP_BIN}/CInterfaceIOWrapper.cpp
		${ASSIMP_BIN}/CInterfaceIOWrapper.h
		${ASSIMP_BIN}/SkeletonMeshBuilder.cpp
		${ASSIMP_BIN}/SkeletonMeshBuilder.h
		${ASSIMP_BIN}/CreateAnimMesh.cpp
		${ASSIMP_BIN}/CreateAnimMesh.h)

target_include_directories(assimp PUBLIC ${ASSIMP}/include/assimp ${ASSIMP}/include ${IRRXML})
set_target_properties(assimp PROPERTIES LIBRARY_OUTPUT_NAME assimp)

#---- BUILD ENGINE ----

add_executable(VixenEngine src/main.cpp src/Window.cpp src/Window.h src/Camera.cpp src/Camera.h src/shaders/Shader.cpp src/shaders/Shader.h src/shaders/Phong.h src/Mesh.cpp src/Mesh.h src/render/EntityRender.cpp src/render/EntityRender.h src/Entity.cpp src/Entity.h src/Loader.cpp src/Loader.h src/Light.cpp src/Light.h src/Player.cpp src/Player.h src/Model.cpp src/Model.h src/Chunk.h src/Material.h src/render/EntityRender.cpp src/render/EntityRender.h src/Generator.cpp src/Generator.h src/render/TerrainRender.cpp src/render/TerrainRender.h src/Image.h src/Texture.h src/shaders/Phong.cpp src/shaders/GuiShader.cpp src/shaders/GuiShader.h src/font/Font.cpp src/font/Font.h src/font/Text.cpp src/font/Text.h src/render/FontRender.cpp src/render/FontRender.h src/font/Character.h src/render/MasterRender.cpp src/render/MasterRender.h)

set(OpenGL_GL_PREFERENCE GLVND)

target_include_directories(VixenEngine PUBLIC ${GLEW}/include ${FREETYPE}/include ${GLFW}/include ${LIBPNG} ${CMAKE_SOURCE_DIR}/contrib/glm)

find_package(OpenGL REQUIRED)
target_include_directories(VixenEngine PUBLIC ${OPENGL_INCLUDE_DIR})

if (WIN32)
	target_link_libraries(VixenEngine png freetype assimp irrxml zlib glfw glew ${OPENGL_LIBRARIES} gdi32 user32 kernel32)
	target_link_libraries(VixenEngine -static winpthread -dynamic)
else()
	target_link_libraries(VixenEngine png freetype assimp irrxml zlib glfw ${OPENGL_LIBRARIES})
endif()