#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

namespace graphics::shaders::phong {
	class Phong : public Shader {
	public:
		Phong(std::string vertex, std::string fragment) : Shader(std::move(vertex), std::move(fragment)) {};
	};
}

