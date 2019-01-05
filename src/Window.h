#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "Image.h"

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity,
                            GLsizei length, const GLchar *message, const void *userParam);

namespace graphics {
	class Window {
	private:
		int fps = 0;
		float FPSTime = 0.0f;
		float lastFPS = 0.0f;
		float lastTime = 0.0f;
		
	public:
		GLFWwindow *window;
		std::string name;
		static int WIDTH;
		static int HEIGHT;
		float deltaTime;
		
		Window(const std::string &name, int width, int height);
		~Window();
		
		bool shouldClose() const;
		
		void update();
		void swap();
		
		void setIcon(std::string icon);
		
	private:
		bool init();
	};
}