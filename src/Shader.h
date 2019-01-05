#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Light.h"
#include "Material.h"

extern std::string resourcePath;

namespace shaders {
	using namespace glm;
	class Shader {
	public:
		GLuint id;
		
		Shader(std::string vertex, std::string fragment);
		~Shader();
		
		void start();
		void stop();
		
	protected:
		virtual void getUniformLocations() = 0;
		
		GLuint loadAndCompile(std::string vertex, std::string fragment);
	};
}

