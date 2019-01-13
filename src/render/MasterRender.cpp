#include "MasterRender.h"

namespace graphics {
	MasterRender::MasterRender() {
		entityRender = new EntityRender();
		fontRender = new FontRender();
		arial = new font::Font("arial.ttf", 12);
		fpsText = new font::Text(arial, "FPS: 0");
		vertexText = new font::Text(arial, "Vertices: 0", glm::vec2(0.0f, fpsText->getBoundingBox().y / graphics::Window::HEIGHT));
		gpuText = new font::Text(arial, reinterpret_cast<const char *>(glGetString(GL_VENDOR)) + std::string(" ") +
		                                reinterpret_cast<const char *>(glGetString(GL_RENDERER)) + std::string(" ") +
		                                reinterpret_cast<const char *>(glGetString(GL_VERSION)), vec2(0.0f,
		                                                                                              vertexText->position.y +
		                                                                                              vertexText->getBoundingBox().y /
		                                                                                              graphics::Window::HEIGHT));
		texts[arial].push_back(fpsText);
		texts[arial].push_back(vertexText);
		texts[arial].push_back(gpuText);
	}
	
	void MasterRender::render() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		camera->update();
		
		entityRender->render(entities, lights);
		fontRender->render(texts);
		
		fps++;
		double currentTime = glfwGetTime();
		if (currentTime - lastTime >= 1.0) {
			fpsText->setText("FPS: " + std::to_string(fps));
			fps = 0;
			lastTime = currentTime;
		}
	}
	
	void MasterRender::addDirectionalLight(vec3 direction, vec3 color) {
		auto light = Light(graphics::Light::DIRECTIONAL);
		light.setDirectional(direction, color);
		lights.push_back(light);
	}
	
	void MasterRender::addPointLight(vec3 position, vec3 color, float quadratic, float linear,
	                                 float constant) {
		auto light = Light(graphics::Light::POINT);
		light.setAttenuation(glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(1.0, 1.0, 1.0), 0.002f, 0.07, 1.0f);
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