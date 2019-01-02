#ifndef VIXENENGINE_SHADER_H
#define VIXENENGINE_SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Light.h"
#include "Material.h"

extern std::string resourcePath;

namespace graphics::shaders {
	using namespace glm;
	class Shader {
	protected:
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
		GLuint id;
		
		Shader(std::string vertex, std::string fragment);
		~Shader();
		
		void start();
		void stop();
		
		void loadProjectionMatrix(mat4 matrix);
		void loadViewMatrix(mat4 matrix);
		void loadModelMatrix(mat4 matrix);
		void loadViewPosition(vec3 position);
		void loadLights(std::vector<graphics::Light*> lights);
		void loadMaterial(Material *material);
		
		void getUniformLocations();
		
	private:
		GLuint loadAndCompile(std::string vertex, std::string fragment);
	};
}

#endif