#ifndef VIXENENGINE_GENERATOR_H
#define VIXENENGINE_GENERATOR_H

#include <glm/glm.hpp>
#include <vector>
#include "Loader.h"
#include "Mesh.h"
#include "Material.h"

namespace terrain {
	using namespace glm;
	using namespace std;
	class Generator {
	private:
		const int seed;
		
	public:
		explicit Generator(int seed = 0) : seed(seed) {};
		graphics::Mesh* flatChunk(int size = 16, int maxVertices = 64);
	};
}

#endif