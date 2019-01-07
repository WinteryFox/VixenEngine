#pragma once

#include "EntityRender.h"
#include "FontRender.h"
#include "TerrainRender.h"

namespace graphics {
	class MasterRender {
	private:
		std::vector<Render> renders;
		
	public:
		unsigned int vertices = 0;
		unsigned int triangles = 0;
		
		
	};
}