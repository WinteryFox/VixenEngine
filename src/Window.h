#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <windows.h>
#include "Image.h"
#include "Loader.h"

namespace graphics {
	class Window {
	private:
		GLFWwindow *window;
		
		const char *name;
		int width;
		int height;
		
		int fps = 0;
		float FPSTime = 0.0f;
		float lastFPS = 0.0f;
		float lastTime = 0.0f;
		float deltaTime = 0.0f;
		
	public:
		Window(const char *name, int width, int height);
		~Window();
		
		bool shouldClose() const;
		
		void update();
		void swap();
		
		GLFWwindow* getWindow();
		float getDeltaTime();
		
		void setIcon(std::string icon);
		
	private:
		bool init();
	};
}