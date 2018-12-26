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

namespace graphics::loader {
	using namespace glm;
	class Loader {
	private:
		const std::string resourcePath;
		
	public:
		explicit Loader(std::string resourcePath);
		
		graphics::model::Model loadModel(std::string file);
		Image loadImage(std::string file);
		GLuint generateTexture(Image image, GLenum filterType);
	};
}

#endif