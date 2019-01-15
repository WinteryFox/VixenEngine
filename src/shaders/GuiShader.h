#pragma once

#include "Shader.h"

namespace shaders {
	class GuiShader : public Shader {
	private:
		GLint projectionLocation;
		GLint colorLocation;
		GLint positionLocation;
		
	public:
		GuiShader();
		
		void getUniformLocations() override;
		
		void loadPosition(float positionX, float positionY);
		void loadProjection(glm::mat4 projection);
		void loadColor(glm::vec3 color);
	};
}
