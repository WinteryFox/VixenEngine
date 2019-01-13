#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "Image.h"

namespace graphics {
	class Window {
	private:
		float lastTime = 0.0f;
		
	public:
		GLFWwindow *window;
		std::string name;
		int width;
		int height;
		float delta;
		bool focused;
		
		Window(const std::string &name, int width, int height);
		~Window();
		
		bool shouldClose() const;
		
		void update();
		void swap();
		
		void setIcon(const std::string &icon);
		
	private:
		bool init();
	};
}

extern graphics::Window* window;

void closeCallback(GLFWwindow* w);
void focusCallback(GLFWwindow* w, int focused);
void bufferCallback(GLFWwindow* w, int width, int height);

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity,
                            GLsizei length, const GLchar *message, const void *userParam);