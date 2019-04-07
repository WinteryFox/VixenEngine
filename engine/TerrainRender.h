#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Chunk.h"
#include "Phong.h"
#include "Camera.h"

namespace graphics {
	class TerrainRender {
	private:
		shaders::Phong* shader;
		
	public:
		TerrainRender(const std::string &resourcePath);
		~TerrainRender();
		
		void render(input::Camera *camera, std::vector<terrain::Chunk*> chunks, std::vector<graphics::Light*> lights);
		
		void prepareMesh(Mesh *mesh);
		
		void prepareInstance(terrain::Chunk *chunk);
	};
}

