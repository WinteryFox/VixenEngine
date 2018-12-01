#ifndef VIXENENGINE_TERRAIN_H
#define VIXENENGINE_TERRAIN_H

#include "Mesh.h"

namespace model {
	class Terrain {
	private:
		graphics::model::Mesh mesh;
		int tileX;
		int tileZ;
		int y;
		
	public:
		Terrain(graphics::model::Mesh mesh, int tileX, int tileZ, int y);
	};
}

#endif