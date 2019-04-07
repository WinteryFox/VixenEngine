#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Light.h"
#include "Material.h"

namespace shaders {
	struct Material {
		GLint texture;
		GLint ambient;
		GLint diffuse;
		GLint specular;
		GLint shininess;
		GLint hasNormal;
	};
	
	struct Light {
		GLint type;
		
		GLint directional;
		
		GLint position;
		GLint color;
		
		GLint quadratic;
		GLint linear;
		GLint constant;
	};
	
	class Shader {
	public:
		GLuint id;
		
		Shader(std::string resourcePath, std::string vertex, std::string fragment);
		~Shader();
		
		void start();
		void stop();
		
		void loadMatrix4f(GLint location, const glm::mat4 &matrix);
		
		void loadVector2f(GLint location, const glm::vec2 &vector);
		
		void loadVector3f(GLint location, const glm::vec3 &vector);
		void loadInteger(GLint location, int integer);
		void loadMaterial(const shaders::Material &materialLocations, graphics::Material *material);
		void loadLight(const shaders::Light &lightLocations, const graphics::Light &light);
		
	protected:
		virtual void getUniformLocations() = 0;
		
		GLuint loadAndCompile(std::string resourcePath, std::string vertex, std::string fragment);
	};
}

