#include <utility>

#include "Window.h"
#include "Loader.h"

namespace graphics {
	Window::Window(const std::string &name, int width, int height) : name(name) {
		this->width = width;
		this->height = height;
		if (!init())
			glfwTerminate();
	}
	
	Window::~Window() {
		glfwSetWindowShouldClose(window, GL_TRUE);
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	
	bool Window::init() {
		if (!glfwInit()) {
			std::cout << "Failed to initialise GLFW" << std::endl;
			return false;
		}
		
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
		
		window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
		if (!window) {
			std::cout << "Failed to create window" << std::endl;
			return false;
		}
		
		setIcon("textures/icon.png");
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialise GLEW" << std::endl;
			return false;
		}
		
		glfwSwapInterval(0);
		
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(window, mode->width / 2 - width / 2, mode->height / 2 - height / 2);
		
		glfwShowWindow(window);
		
		glfwSetWindowFocusCallback(window, focusCallback);
		glfwSetFramebufferSizeCallback(window, bufferCallback);
		
		return true;
	}
	
	void Window::update() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		
		auto current = static_cast<float>(glfwGetTime());
		delta = current - lastTime;
		lastTime = current;
	}
	
	void Window::swap() {
		glfwSwapBuffers(window);
	}
	
	bool Window::shouldClose() const {
		return glfwWindowShouldClose(window) == GLFW_TRUE;
	}
	
	void Window::setIcon(const std::string &icon) {
		graphics::Image* temp = graphics::loader::Loader::loadImage(icon);
		
		GLFWimage images[1];
		images[0].width = temp->width;
		images[0].height = temp->height;
		images[0].pixels = temp->data;
		
		glfwSetWindowIcon(window, 1, images);
	}
}

void bufferCallback(GLFWwindow* w, int width, int height) {
	window->width = width;
	window->height = height;
	glViewport(0, 0, width, height);
}

void focusCallback(GLFWwindow* w, int focused) {
	window->focused = focused == GLFW_TRUE;
}

void APIENTRY glDebugOutput(GLenum source,
                                    GLenum type,
                                    GLuint id,
                                    GLenum severity,
                                    GLsizei length,
                                    const GLchar *message,
                                    const void *userParam)
{
	// ignore non-significant error/warning codes
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
	
	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " <<  message << std::endl;
	
	switch (source)
	{
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;
	
	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;
	
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}
