#ifndef VIXENENGINE_WINDOW_H
#define VIXENENGINE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace graphics {
	class Window {
	public:
		Window(const char *name, int width, int height);
		~Window();
		
		bool shouldClose() const;
		
		void update();
		void swap();
		
	private:
		bool init();
		
	private:
		GLFWwindow *window;
		
		const char *name;
		int width;
		int height;
	};
}

#endif