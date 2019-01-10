#include "MasterRender.h"
#include "../Loader.h"

namespace graphics {
	MasterRender::MasterRender() {
		entityRender = new EntityRender();
	}
	
	void MasterRender::render() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		camera->update();
		
		entityRender->render(entities, lights);
	}
	
	void MasterRender::addDirectionalLight(vec3 direction, vec3 color) {
		auto* light = new Light(graphics::Light::DIRECTIONAL);
		light->setDirectional(direction, color);
		lights.push_back(light);
	}
	
	void MasterRender::addPointLight(vec3 position, vec3 color, float quadratic, float linear,
	                                 float constant) {
		auto* light = new Light(graphics::Light::POINT);
		light->setAttenuation(glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(1.0, 1.0, 1.0), 0.002f, 0.07, 1.0f);
		lights.push_back(light);
	}
	
	void MasterRender::addEntity(const std::string &file, vec3 position, vec3 rotation, float scale) {
		objects::entity::Entity* entity = new objects::entity::Entity(graphics::loader::Loader::loadModel(file), position, rotation, scale);
		for (Mesh* mesh : entity->model->getMeshes()) {
			vertices += mesh->getVertices().size();
		}
		entities.push_back(entity);
	}
}