#ifndef VIXENENGINE_LOADER_H
#define VIXENENGINE_LOADER_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include "Mesh.h"

namespace graphics::loader {
	using namespace glm;
	class Loader {
	public:
		graphics::model::Mesh loadMesh(const char *path);
	};
}

#endif