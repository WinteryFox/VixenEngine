#ifndef VIXENENGINE_WINDOW_H
#define VIXENENGINE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace graphics {
	class Window {
	private:
		GLFWwindow *window;
		
		const char *name;
		int width;
		int height;
		
		int fps = 0;
		double lastTime = glfwGetTime();
		float deltaTime = 0;
		
	public:
		Window(const char *name, int width, int height);
		~Window();
		
		bool shouldClose() const;
		
		void update();
		void swap();
		
		GLFWwindow* getWindow();
		float getDeltaTime();
		
	private:
		bool init();
	};
}

#endif