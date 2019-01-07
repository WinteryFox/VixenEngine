#pragma once

#include "../shaders/Shader.h"

namespace graphics {
	class Render {
	public:
		shaders::Shader* shader = nullptr;
		
		virtual void render() = 0;
	};
}