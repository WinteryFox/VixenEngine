#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../Light.h"
#include "../Material.h"

extern std::string resourcePath;

namespace shaders {
	struct Material {
		GLint texture;
		GLint ambient;
		GLint diffuse;
		GLint specular;
		GLint shininess;
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
		
		Shader(std::string vertex, std::string fragment);
		~Shader();
		
		void start();
		void stop();
		
		void loadMatrix4f(GLuint location, const glm::mat4 &matrix);
		void loadVector2f(GLuint location, const glm::vec2 &vector);
		void loadVector3f(GLuint location, const glm::vec3 &vector);
		void loadMaterial(const shaders::Material &materialLocations, const graphics::Material &material);
		void loadLight(const shaders::Light &lightLocations, const graphics::Light &light);
		
	protected:
		virtual void getUniformLocations() = 0;
		
		GLuint loadAndCompile(std::string vertex, std::string fragment);
	};
}

