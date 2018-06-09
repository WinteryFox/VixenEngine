#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef _WIN32
#define GLEW_STATIC
#endif

int main() {
	if (!glfwInit()) {
		std::cout << "Failed to initialise GLFW" << std::endl;
		return 1;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
	glfwSwapInterval(0);
	
	GLFWwindow* window = glfwCreateWindow(1028, 720, "Vixen Engine", nullptr, nullptr);
	if (!window) {
		fprintf(stderr, "Failed to create window");
		return false;
	}
	
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return false;
	}
	
	glGetError();
	
	while (true) {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	return 0;
}