#include "Phong.h"

namespace shaders {
	Phong::Phong() : Shader("phong.vert", "phong.frag") {
		getUniformLocations();
	}
	
	void Phong::getUniformLocations() {
		modelMatrixLocation = glGetUniformLocation(id, "model");
		viewMatrixLocation = glGetUniformLocation(id, "view");
		projectionMatrixLocation = glGetUniformLocation(id, "projection");
		viewPositionLocation = glGetUniformLocation(id, "viewPos");
		
		directionalLightColorLocation = glGetUniformLocation(id, "dirLight.color");
		directionalLightDirectionLocation = glGetUniformLocation(id, "dirLight.direction");
		
		lightCountLocation = glGetUniformLocation(id, "lightCount");
		for (unsigned int i = 0; i < 16; i++) {
			lightLocations[i] = shaders::Light{
					.type = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append(
							"].type").c_str()),
					
					.directional = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append(
							"].directional").c_str()),
					
					.position = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append(
							"].position").c_str()),
					.color = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append(
							"].color").c_str()),
					
					.quadratic = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append(
							"].quadratic").c_str()),
					.linear = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append(
							"].linear").c_str()),
					.constant = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append(
							"].constant").c_str()),
			};
		}
		
		materialLocation.ambient = glGetUniformLocation(id, "material.ambient");
		materialLocation.diffuse = glGetUniformLocation(id, "material.diffuse");
		materialLocation.specular = glGetUniformLocation(id, "material.specular");
		materialLocation.shininess = glGetUniformLocation(id, "material.shininess");
	}
	
	void Phong::loadProjectionMatrix(const glm::mat4 &matrix) {
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
	}
	
	void Phong::loadViewMatrix(const glm::mat4 &matrix) {
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
	}
	
	void Phong::loadModelMatrix(const glm::mat4 &matrix) {
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
	}
	
	void Phong::loadViewPosition(const glm::vec3 &position) {
		glUniform3fv(viewPositionLocation, 1, &position[0]);
	}
	
	void Phong::loadLights(const std::vector<graphics::Light> &lights) {
		glUniform1i(lightCountLocation, lights.size());
		for (unsigned int i = 0; i < lights.size(); i++) {
			loadLight(lightLocations[i], lights[i]);
		}
	}
	
	void Phong::loadMaterial(const graphics::Material &material) {
		Shader::loadMaterial(materialLocation, material);
	}
}