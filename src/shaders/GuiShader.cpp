#include "GuiShader.h"

namespace shaders {
	GuiShader::GuiShader() : Shader("gui.vert", "gui.frag") {
		getUniformLocations();
	}
	
	void GuiShader::getUniformLocations() {
		projectionLocation = glGetUniformLocation(id, "projection");
		colorLocation = glGetUniformLocation(id, "color");
		positionLocation = glGetUniformLocation(id, "pos");
	}
	
	void GuiShader::loadColor(glm::vec3 color) {
		loadVector3f(colorLocation, color);
	}
	
	void GuiShader::loadProjection(glm::mat4 projection) {
		loadMatrix4f(projectionLocation, projection);
	}
	
	void GuiShader::loadPosition(float positionX, float positionY) {
		loadVector2f(positionLocation, glm::vec2(positionX, positionY));
	}
}