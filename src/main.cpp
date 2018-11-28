#include <GL/glew.h>
#include "Entity.h"
#include "Window.h"
#include "Render.h"
#include "Phong.h"
#include "Loader.h"
#include "Light.h"

int main() {
	auto *window = new graphics::Window("Vixen Engine", 1020, 780);
	
	const std::string resourcePath = "../resources/";
	
	glGetError();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	auto *camera = new input::Camera(glm::vec3(0.0, 0.0, 5.0), 70, 5, 2);
	
	auto *loader = new graphics::loader::Loader();
	
	graphics::shaders::Shader *phong = new graphics::shaders::phong::Phong(resourcePath + "shaders/phong.vert", resourcePath + "shaders/phong.frag");
	
	auto *render = new graphics::model::Render();
	render->use(phong);
	
	auto *light = new graphics::Light(graphics::Light::Type::POINT);
	light->setAttenuation(glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(1.0, 1.0, 1.0), 0.00000002f, 0.0000007, 1.0f);
	render->addLight(light);
	
	graphics::model::Model model = loader->loadModel(resourcePath + "models/kizuna/kizuna.dae");
	render->add(new objects::entity::Entity(model, glm::vec3(0.0), glm::vec3(-90.0f, 0.0f, 0.0f)));
	
	while (!window->shouldClose()) {
		window->update();
		camera->update(window);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		
		render->render(camera);
		
		window->swap();
		
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << error << ": " << glewGetErrorString(error) << std::endl;
	}
	return 0;
}