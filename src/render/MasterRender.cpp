#include "MasterRender.h"

namespace graphics {
	MasterRender::MasterRender() {
		entityRender = new EntityRender();
		fontRender = new FontRender();
		
		arial = new font::Font("arial.ttf", 14);
		fpsText = new font::Text(arial, "FPS: 0");
		vertexText = new font::Text(arial, "Vertices: 0", glm::vec2(0.0f, fpsText->boundingBox.y));
		gpuText = new font::Text(arial, std::string("GPU: ") +
		                                reinterpret_cast<const char *>(glGetString(GL_RENDERER)) + std::string(" ") +
		                                reinterpret_cast<const char *>(glGetString(GL_VERSION)),
		                         vec2(0.0f, vertexText->position.y + vertexText->boundingBox.y));
		
		texts[arial].push_back(fpsText);
		texts[arial].push_back(vertexText);
		texts[arial].push_back(gpuText);
	}
	
	MasterRender::~MasterRender() {
		delete arial;
		delete fpsText;
		delete vertexText;
		delete gpuText;
	}
	
	void MasterRender::render() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		window->update();
		
		double newFrame = glfwGetTime();
		double frameTime = newFrame - lastFrame;
		lastFrame = newFrame;
		
		accumulator += frameTime;
		
		while (accumulator >= tickrate) {
			camera->update(frameTime, tickrate);
			accumulator -= tickrate;
			// TODO: Fix this.
		}
		
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
	
	Entity *MasterRender::addEntity(const std::string &file, vec3 position, vec3 rotation, float scale) {
		graphics::Model *model = graphics::loader::Loader::loadModel(file);
		auto *entity = new objects::entity::Entity(model, position, rotation, scale);
		
		for (Mesh *mesh : model->getMeshes()) {
			vertices += mesh->vertexCount;
		}
		
		vertexText->setText("Vertices: " + std::to_string(vertices));
		entities.push_back(entity);
		return entity;
	}
	
	void MasterRender::addTerrain(int gridX, int gridZ) {
		Mesh *mesh = terrain::Generator::flatChunk();
		vertices += mesh->vertexCount;
		vertexText->setText("Vertices: " + std::to_string(vertices));
		terrains.push_back(mesh);
	}
	
	graphics::Light *MasterRender::addDirectionalLight(const vec3 &direction, const dvec3 &color) {
		auto light = new graphics::Light(graphics::Light::Type::DIRECTIONAL);
		light->setDirectional(direction, color);
		lights.emplace_back(light);
		return light;
	}
	
	graphics::Light *MasterRender::addDirectionalTemperatureLight(const vec3 &direction, unsigned int temperature) {
		auto light = new graphics::Light(graphics::Light::Type::DIRECTIONAL);
		light->direction = direction;
		light->setTemperature(temperature);
		lights.emplace_back(light);
		return light;
	}
	
	graphics::Light *
	MasterRender::addPointLight(const vec3 &position, const dvec3 &color, float quadratic, float linear,
	                            float constant) {
		auto light = new graphics::Light(graphics::Light::Type::POINT);
		light->setAttenuation(position, color, quadratic, linear, constant);
		lights.emplace_back(light);
		return light;
	}
	
	graphics::Light *
	MasterRender::addPointTemperatureLight(const vec3 &position, unsigned int temperature, float quadratic,
	                                       float linear,
	                                       float constant) {
		auto light = new graphics::Light(graphics::Light::Type::POINT);
		light->position = position;
		light->setTemperature(temperature);
		light->quadratic = quadratic;
		light->linear = linear;
		light->constant = constant;
		lights.emplace_back(light);
		return light;
	}
}