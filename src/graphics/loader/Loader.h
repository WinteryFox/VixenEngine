#ifndef VIXENENGINE_LOADER_H
#define VIXENENGINE_LOADER_H

#include <vector>
#include <glm/glm.hpp>
#include "../model/Mesh.h"

namespace graphics::loader {
	using namespace glm;
	class Loader {
	private:
		std::vector<graphics::model::Mesh> meshes;
	
	public:
		graphics::model::Mesh loadMesh(const char *path);
	};
}

#endif