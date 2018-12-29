#include <GL/glew.h>
#include "Entity.h"
#include "Window.h"
#include "Render.h"
#include "Phong.h"
#include "Loader.h"
#include "Light.h"
#include "Chunk.h"
#include "Generator.h"

int main() {
	auto *window = new graphics::Window("Vixen Engine", 1280, 720);
	
	const std::string resourcePath = "../resources/";
	
	glGetError();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	auto *camera = new input::Camera(glm::vec3(0.0, 0.0, 5.0), 70, 5, 2);
	
	auto *loader = new graphics::loader::Loader("../resources/");
	
	graphics::shaders::Shader *phong = new graphics::shaders::phong::Phong(resourcePath + "shaders/phong.vert", resourcePath + "shaders/phong.frag");
	
	auto *render = new graphics::Render();
	render->use(phong);
	
	auto *light = new graphics::Light(graphics::Light::Type::POINT);
	light->setAttenuation(glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(1.0, 1.0, 1.0), 0.00000002f, 0.0000007, 1.0f);
	render->addLight(light);
	
	graphics::model::Model model = loader->loadModel("models/kizuna/kizuna.dae");
	render->add(new objects::entity::Entity(model, glm::vec3(0.0), glm::vec3(0.0f, 0.0f, 0.0f)));
	
	auto *generator = new terrain::Generator();
	auto *chunk = new terrain::Chunk(generator->flatChunk(), 0, 0, 0);
	
	std::vector<graphics::Mesh*> meshes;
	meshes.push_back(chunk->mesh);
	render->add(new objects::entity::Entity(graphics::Model(meshes), glm::vec3(0), glm::vec3(0), 1.0f));
	
	while (!window->shouldClose()) {
		window->update();
		camera->update(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		render->render(camera);
		
		window->swap();
		
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << error << ": " << glewGetErrorString(error) << std::endl;
	}
	return 0;
}