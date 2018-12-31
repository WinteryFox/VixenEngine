#ifndef VIXENENGINE_LOADER_H
#define VIXENENGINE_LOADER_H

#include <stdlib.h>
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
#include "Image.h"

extern std::string resourcePath;

namespace graphics::loader {
	using namespace glm;
	class Loader {
	public:
		static graphics::model::Model* loadModel(std::string file);
		static Image* loadImage(std::string file);
		static GLuint generateTexture(Image* image, GLenum wrap = GL_REPEAT, GLenum filter = GL_NEAREST);
	};
}

#endif