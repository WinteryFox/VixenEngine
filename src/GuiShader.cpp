#include "GuiShader.h"

namespace shaders {
	GuiShader::GuiShader() : Shader("gui.vert", "gui.frag") {
		getUniformLocations();
	}
	
	void GuiShader::getUniformLocations() {
		positionLocation = glGetUniformLocation(id, "translation");
		colorLocation = glGetUniformLocation(id, "color");
	}
	
	void GuiShader::loadColor(glm::vec3 color) {
		glUniform3fv(colorLocation, 1, &color[0]);
	}
	
	void GuiShader::loadPosition(glm::vec2 position) {
		glUniform2fv(positionLocation, 1, &position[0]);
	}
}