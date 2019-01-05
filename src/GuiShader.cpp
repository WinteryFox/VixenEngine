#include "GuiShader.h"

namespace shaders {
	GuiShader::GuiShader() : Shader("gui.vert", "gui.frag") {
		getUniformLocations();
	}
	
	void GuiShader::getUniformLocations() {
		positionLocation = glGetUniformLocation(id, "projection");
		colorLocation = glGetUniformLocation(id, "color");
	}
	
	void GuiShader::loadColor(glm::vec3 color) {
		glUniform3fv(colorLocation, 1, &color[0]);
	}
	
	void GuiShader::loadProjection(glm::mat4 projection) {
		glUniformMatrix4fv(positionLocation, 1, GL_FALSE, &projection[0][0]);
	}
}