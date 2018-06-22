#ifndef VIXENENGINE_LOADER_H
#define VIXENENGINE_LOADER_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "../../irrxml/irrXML.h"
#include "../model/Mesh.h"

namespace graphics::loader {
	using namespace irr::io;
	using namespace glm;
	class Loader {
	public:
		graphics::model::Mesh* loadMesh(const char *path);
	};
}

#endif