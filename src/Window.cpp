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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
		
		window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		if (!window) {
			std::cout << "Failed to create window" << std::endl;
			return false;
		}
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialise GLEW" << std::endl;
			return false;
		}
		
		glfwSwapInterval(0);
		
		setIcon("textures/icon.png");
		
		return true;
	}
	
	void Window::update() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		
		auto current = static_cast<float>(glfwGetTime());
		deltaTime = current - lastTime;
		FPSTime = current - lastFPS;
		lastTime = current;
		fps++;
		if (FPSTime >= 1.0) {
			std::cout << fps << " fps" << std::endl;
			fps = 0;
			lastFPS = current;
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
	
	void Window::setIcon(std::string icon) {
		graphics::Image* temp = graphics::loader::Loader::loadImage(icon);
		
		GLFWimage images[1];
		images[0].width = temp->width;
		images[0].height = temp->height;
		images[0].pixels = temp->data;
		
		glfwSetWindowIcon(window, 1, images);
	}
}
