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
			lightColorLocation[i] = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append("].color").c_str());
			lightPositionLocation[i] = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append("].position").c_str());
			lightQuadraticLocation[i] = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append("].quadratic").c_str());
			lightLinearLocation[i] = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append("].linear").c_str());
			lightConstantLocation[i] = glGetUniformLocation(id, std::string("lights[").append(std::to_string(i)).append("].constant").c_str());
		}
		
		materialAmbientLocation = glGetUniformLocation(id, "material.ambient");
		materialDiffuseLocation = glGetUniformLocation(id, "material.diffuse");
		materialSpecularLocation = glGetUniformLocation(id, "material.specular");
		materialShininessLocation = glGetUniformLocation(id, "material.shininess");
	}
	
	void Phong::loadProjectionMatrix(glm::mat4 matrix) {
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
	}
	
	void Phong::loadViewMatrix(glm::mat4 matrix) {
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
	}
	
	void Phong::loadModelMatrix(glm::mat4 matrix) {
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
	}
	
	void Phong::loadViewPosition(glm::vec3 position) {
		glUniform3fv(viewPositionLocation, 1, &position[0]);
	}
	
	void Phong::loadLights(std::vector<graphics::Light*> lights) {
		glUniform1i(lightCountLocation, lights.size());
		for (int i = 0; i < lights.size(); ++i) {
			graphics::Light *light = lights[i];
			if (light->getType() == graphics::Light::DIRECTIONAL) {
				glUniform3fv(directionalLightDirectionLocation, 1, &light->getDirection()[0]);
				glUniform3fv(directionalLightColorLocation, 1, &light->getColor()[0]);
			} else {
				glUniform3fv(lightColorLocation[i], 1, &light->getColor()[0]);
				glUniform3fv(lightPositionLocation[i], 1, &light->getPosition()[0]);
				glUniform1f(lightQuadraticLocation[i], light->getQuadratic());
				glUniform1f(lightLinearLocation[i], light->getLinear());
				glUniform1f(lightConstantLocation[i], light->getConstant());
			}
		}
	}
	
	void Phong::loadMaterial(graphics::Material *material) {
		glUniform3fv(materialAmbientLocation, 1, &material->ambient[0]);
		glUniform3fv(materialDiffuseLocation, 1, &material->diffuse[0]);
		glUniform3fv(materialSpecularLocation, 1, &material->specular[0]);
		glUniform1f(materialShininessLocation, material->shininess);
	}
}