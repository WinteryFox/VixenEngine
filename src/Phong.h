#ifndef VIXWORLD_MAT_HPP
#define VIXWORLD_MAT_HPP

#include <glm/glm.hpp>
#include "Shader.h"

namespace graphics::shaders::phong {
	class Phong : public Shader {
	public:
		Phong(const char *vertexFilePath, const char *fragmentFilePath);
	};
}

#endif