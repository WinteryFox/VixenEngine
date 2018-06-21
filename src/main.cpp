#include <GL/glew.h>
#include "graphics/Window.h"
#include "graphics/render/EntityRender.h"
#include "graphics/shaders/phong/Phong.h"
#include "graphics/loader/Loader.h"

#ifdef _WIN32
#define GLEW_STATIC
#endif

int main() {
	auto *window = new graphics::Window("Vixen Engine", 1020, 780);
	
	glGetError();
	
	auto *loader = new graphics::loader::Loader();
	
	graphics::shaders::Shader *phong = new graphics::shaders::phong::Phong("../src/graphics/shaders/phong/phong.vert", "../src/graphics/shaders/phong/phong.frag");
	
	std::vector<glm::vec3> nothing = std::vector<glm::vec3>{glm::vec3(0.0f)};
	std::vector<glm::vec2> nothing1 = std::vector<glm::vec2>{glm::vec2(0.0f)};
	std::vector<unsigned int> nothing2 = std::vector<unsigned int>{0};
	
	graphics::model::Entity *entity = new graphics::model::Entity(loader->loadMesh(""), glm::vec3(0.0), glm::vec3(0.0), 0.0f);
	auto *render = new graphics::model::EntityRender();
	render->use(phong);
	render->add(entity);
	
	while (!window->shouldClose()) {
		window->update();
		glClearColor(0.0, 1.0, 1.0, 1.0);
		
		render->render();
		
		phong->stop();
		window->swap();
	}
	
	return 0;
}