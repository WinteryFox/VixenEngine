#pragma once

#include "Mesh.h"

namespace terrain {
	class Chunk {
	private:
		
		int tileX;
		int tileZ;
		int y;
		
	public:
		graphics::Mesh *mesh;
		Chunk(graphics::Mesh *mesh, int tileX, int tileZ, int y) : mesh(mesh), tileX(tileX), tileZ(tileZ), y(y) {};
	};
}

