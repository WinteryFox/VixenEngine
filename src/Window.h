#pragma once

#ifdef __WIN32__
#include <GL/glew.h>
#elif __APPLE__

#include <OpenGL/gl.h>

#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "Image.h"

namespace graphics {
	class Window {
	public:
		GLFWwindow *window;
		std::string name;
		
		int glVersionMajor;
		int glVersionMinor;
		
		Window(const std::string &name, int width, int height);
		~Window();
		
		bool shouldClose() const;
		
		void update();
		void swap();
		
		void setIcon(const std::string &icon);
		
		glm::vec2 size();
		bool focused();
		
	private:
		bool init(int width, int height);
	};
}

void focusCallback(GLFWwindow* w, int focused);
void bufferCallback(GLFWwindow* w, int width, int height);

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity,
                            GLsizei length, const GLchar *message, const void *userParam);