#ifndef VIXENENGINE_LOADER_H
#define VIXENENGINE_LOADER_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <png.h>
#include "Mesh.h"
#include "Model.h"

namespace graphics::loader {
	using namespace glm;
	class Loader {
	public:
		graphics::model::Model loadModel(const std::string &path);
		
		GLuint generateTexture(const GLint format, const unsigned int width, const unsigned int height, png_byte *data);
		GLuint loadTexture(const char *path);
	};
}

#endif