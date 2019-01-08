#pragma once

#include "EntityRender.h"
#include "FontRender.h"
#include "TerrainRender.h"

input::Camera camera;

namespace graphics {
	class MasterRender {
	private:
		EntityRender entityRender;
		
	public:
		unsigned int vertices = 0;
		unsigned int triangles = 0;
		
		MasterRender();
		
		void render();
	};
}