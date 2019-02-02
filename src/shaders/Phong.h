#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "../Material.h"

namespace shaders {
	class Phong : public Shader {
	private:
		GLint projectionMatrixLocation;
		GLint viewMatrixLocation;
		GLint modelMatrixLocation;
		
		GLint viewPositionLocation;
		
		GLint lightCountLocation;
		std::vector<shaders::Light> lightLocations;
		
		shaders::Material materialLocation;
		
		GLint tDiffuseLocation;
		
		GLint tNormalLocation;
		
	public:
		Phong();
		
		void getUniformLocations() override;
		
		void loadProjectionMatrix(const glm::mat4 &matrix);
		void loadViewMatrix(const glm::mat4 &matrix);
		void loadModelMatrix(const glm::mat4 &matrix);
		void loadViewPosition(const glm::vec3 &position);
		
		void loadLights(const std::vector<graphics::Light *> &lights);
		
		void loadMaterial(graphics::Material *material);
	};
}

