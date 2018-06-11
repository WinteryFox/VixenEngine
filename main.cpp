
#include <GL/glew.h>
#include "graphics/Window.h"

#ifdef _WIN32
#define GLEW_STATIC
#endif

int main() {
	auto *window = new graphics::Window("Vixen Engine", 1020, 780);
	
	glGetError();
	
	while (!window->shouldClose()) {
		window->update();
		glClearColor(0.0, 1.0, 1.0, 1.0);
		window->swap();
	}
	
	return 0;
}