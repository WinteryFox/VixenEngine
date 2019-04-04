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

namespace graphics::loader {
	using namespace glm;
	class Loader {
	private:
		static void readData(png_structp readPointer, png_bytep data, png_size_t length);
		
	public:
		static graphics::model::Model* loadModel(std::string file);
		
		static void calculateTangentSpace(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uvs,
		                                  const std::vector<unsigned int> &indices,
		                                  std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &bitangents);
		static graphics::Image* loadImage(std::string file, bool flipped = false);
		
		static graphics::Texture *generateTexture(Image *image);
		
		static graphics::Texture *generateTexture(const std::string &texture);
	};
}