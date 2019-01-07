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
		
		GLint directionalLightColorLocation;
		GLint directionalLightDirectionLocation;
		
		GLint lightCountLocation;
		GLint lightColorLocation[16];
		GLint lightPositionLocation[16];
		GLint lightQuadraticLocation[16];
		GLint lightLinearLocation[16];
		GLint lightConstantLocation[16];
		
		GLint materialAmbientLocation;
		GLint materialDiffuseLocation;
		GLint materialSpecularLocation;
		GLint materialShininessLocation;
		
	public:
		Phong();
		
		void getUniformLocations() override;
		
		void loadLights(std::vector<graphics::Light*> lights);
		void loadMaterial(graphics::Material *material);
	};
}

