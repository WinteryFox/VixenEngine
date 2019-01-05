#pragma once

#include "Shader.h"

namespace shaders {
	class GuiShader : public Shader {
	private:
		GLint positionLocation;
		GLint colorLocation;
		
	public:
		GuiShader();
		
		void getUniformLocations() override;
		
		void loadPosition(glm::vec2 position);
		void loadColor(glm::vec3 color);
	};
}
