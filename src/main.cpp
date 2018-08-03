#include <GL/glew.h>
#include "Window.h"
#include "Render.h"
#include "Phong.h"
#include "Loader.h"

#ifdef _WIN32
#define GLEW_STATIC
#endif

int main() {
	auto *window = new graphics::Window("Vixen Engine", 1020, 780);
	
	glGetError();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	auto *camera = new input::Camera(glm::vec3(0.0, 0.0, 5.0));
	
	auto *loader = new graphics::loader::Loader();
	
	graphics::shaders::Shader *phong = new graphics::shaders::phong::Phong("../src/resources/shaders/phong.vert", "../src/resources/shaders/phong.frag");
	
	graphics::model::Mesh mesh = loader->loadMesh("../src/resources/tree.dae");
	auto *entity = new objects::entity::Entity(mesh);
	auto *render = new graphics::model::Render();
	render->use(phong);
	render->add(entity);
	
	while (!window->shouldClose()) {
		window->update();
		camera->update(window);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		
		render->render(camera);
		
		window->swap();
		
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << error << ": " << glewGetErrorString(error) << std::endl;
	}
	return 0;
}