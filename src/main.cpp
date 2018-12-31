#include <GL/glew.h>
#include "Entity.h"
#include "Window.h"
#include "Render.h"
#include "Phong.h"
#include "Loader.h"
#include "Light.h"
#include "Chunk.h"
#include "Generator.h"

std::string resourcePath = "../resources/";

int main() {
	auto *window = new graphics::Window("Vixen Engine", 1280, 720);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	Image* missing = graphics::loader::Loader::loadImage(resourcePath + "textures/missing.png");
	glTexImage2D(GL_TEXTURE_2D, 0, missing->format, missing->width, missing->height, 0, missing->format, GL_UNSIGNED_BYTE, missing->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glGetError();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	auto* camera = new input::Camera(glm::vec3(0.0, 0.0, 5.0), 70, 5, 2);
	
	graphics::shaders::Shader *phong = new graphics::shaders::phong::Phong(resourcePath + "shaders/phong.vert", resourcePath + "shaders/phong.frag");
	
	auto* render = new graphics::Render();
	render->use(phong);
	
	auto* light = new graphics::Light(graphics::Light::Type::POINT);
	light->setAttenuation(glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(1.0, 1.0, 1.0), 0.00000002f, 0.0000007, 1.0f);
	render->addLight(light);
	
	graphics::model::Model* model = graphics::loader::Loader::loadModel("models/kizuna/kizuna.dae");
	auto* entity = new objects::entity::Entity(model);
	render->add(entity);
	
	auto* generator = new terrain::Generator();
	auto* chunk = new terrain::Chunk(generator->flatChunk(), 0, 0, 0);
	
	std::vector<graphics::Mesh*> meshes;
	meshes.push_back(chunk->mesh);
	render->add(new objects::entity::Entity(new graphics::Model(meshes), glm::vec3(0), glm::vec3(0), 1.0f));
	
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