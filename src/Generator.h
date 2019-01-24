#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Loader.h"
#include "Material.h"
#include "Chunk.h"

namespace terrain {
	using namespace glm;
	using namespace std;
	class Generator {
	public:
		static terrain::Chunk *flatChunk(int gridX, int gridZ, int size = 16, int maxVertices = 64);
	};
}

