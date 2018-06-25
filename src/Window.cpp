#include <iostream>
#include "Window.h"

namespace graphics {
	Window::Window(const char *name, int width, int height) : name(name), width(width), height(height) {
		if (!init())
			glfwTerminate();
	}
	
	Window::~Window() {
		glfwSetWindowShouldClose(window, GL_TRUE);
		glfwTerminate();
	}
	
	bool Window::init() {
		if (!glfwInit()) {
			std::cout << "Failed to initialise GLFW" << std::endl;
			return false;
		}
		
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
		glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
		glfwSwapInterval(0);
		
		window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		if (!window) {
			std::cout << "Failed to create window" << std::endl;
			return false;
		}
		
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialise GLEW" << std::endl;
			return false;
		}
		
		return true;
	}
	
	void Window::update() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		
		auto current = static_cast<float>(glfwGetTime());
		deltaTime = static_cast<float>(current - lastTime);
		fps++;
		if (deltaTime >= 1.0) {
			std::cout << fps << " fps" << std::endl;
			fps = 0;
			lastTime = glfwGetTime();
		}
	}
	
	void Window::swap() {
		glfwSwapBuffers(window);
	}
	
	bool Window::shouldClose() const {
		return glfwWindowShouldClose(window) == 1;
	}
	
	GLFWwindow *Window::getWindow() {
		return window;
	}
	
	float Window::getDeltaTime() {
		return deltaTime;
	}
}
