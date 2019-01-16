#pragma once

#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Model.h"
#include "Image.h"
#include "Texture.h"

extern std::string resourcePath;

namespace graphics::loader {
	using namespace glm;
	class Loader {
	private:
		static void readData(png_structp readPointer, png_bytep data, png_size_t length);
		
	public:
		static graphics::model::Model* loadModel(std::string file);
		static graphics::Image* loadImage(std::string file, bool flipped = false);
		static graphics::Texture* generateTexture(Image* image, GLint filter = GL_NEAREST);
	};
}