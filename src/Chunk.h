#pragma once

#include "Mesh.h"

namespace terrain {
	class Chunk {
	public:
		int gridX;
		int gridZ;
		int y;
		float size;
		graphics::Mesh *mesh;
		
		Chunk(graphics::Mesh *mesh, float size, int tileX, int tileZ, int y) : mesh(mesh), size(size), gridX(tileX), gridZ(tileZ), y(y) {
		
		};
	};
}

