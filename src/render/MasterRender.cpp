#include "MasterRender.h"

double deltaTime = 0.0;

namespace graphics {
	MasterRender::MasterRender() {
		entityRender = new EntityRender();
		fontRender = new FontRender();
		arial = new font::Font("arial.ttf", 12);
		fpsText = new font::Text(arial, "FPS: 0");
		vertexText = new font::Text(arial, "Vertices: 0", glm::vec2(0.0f, fpsText->boundingBox.y));
		gpuText = new font::Text(arial, reinterpret_cast<const char *>(glGetString(GL_VENDOR)) + std::string(" ") +
		                                reinterpret_cast<const char *>(glGetString(GL_RENDERER)) + std::string(" ") +
		                                reinterpret_cast<const char *>(glGetString(GL_VERSION)), vec2(0.0f,
		                                                                                              vertexText->position.y +
		                                                                                              vertexText->boundingBox.y));
		texts[arial].push_back(fpsText);
		texts[arial].push_back(vertexText);
		texts[arial].push_back(gpuText);
	}
	
	void MasterRender::render() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		window->update();
		
		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;
		
		accumulator += frameTime;
		
		while (accumulator >= tickrate) {
			camera->update();
			accumulator -= tickrate;
			deltaTime += tickrate;
			std::cout << deltaTime << std::endl;
		}
		std::cout << "end" << std::endl;
		
		entityRender->render(entities, lights);
		fontRender->render(texts);
		
		fps++;
		double currentTime = glfwGetTime();
		if (currentTime - lastTime >= 1.0) {
			fpsText->setText("FPS: " + std::to_string(fps));
			fps = 0;
			lastTime = currentTime;
		}
		
		window->swap();
	}
	
	void MasterRender::addDirectionalLight(vec3 direction, vec3 color) {
		auto light = Light(graphics::Light::DIRECTIONAL);
		light.setDirectional(direction, color);
		lights.push_back(light);
	}
	
	void MasterRender::addPointLight(vec3 position, vec3 color, float quadratic, float linear,
	                                 float constant) {
		auto light = Light(graphics::Light::POINT);
		light.setAttenuation(position, color, quadratic, linear, constant);
		lights.push_back(light);
	}
	
	void MasterRender::addEntity(const std::string &file, vec3 position, vec3 rotation, float scale) {
		objects::entity::Entity entity = objects::entity::Entity(graphics::loader::Loader::loadModel(file), position,
		                                                         rotation, scale);
		for (Mesh *mesh : entity.model->getMeshes()) {
			vertices += mesh->vertexCount;
		}
		vertexText->setText("Vertices: " + std::to_string(vertices));
		entities.push_back(entity);
	}
	
	void MasterRender::addTerrain(int gridX, int gridZ) {
		Mesh* mesh = terrain::Generator::flatChunk();
		vertices += mesh->vertexCount;
		vertexText->setText("Vertices: " + std::to_string(vertices));
		terrains.push_back(mesh);
	}
}