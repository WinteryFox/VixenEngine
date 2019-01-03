#pragma once

#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Entity.h"
#include "Camera.h"
#include "Light.h"

namespace graphics {
	using namespace objects::entity;
	class Render {
	private:
		graphics::shaders::Shader *shader;
		std::vector<Entity*> entities;
		std::vector<graphics::Light*> lights;
	
	public:
		void render(input::Camera *camera);
		void use(graphics::shaders::Shader *shader);
		void add(Entity *entity);
		void addLight(graphics::Light *light);
	
	private:
		void prepareMesh(const Mesh *mesh);
		void prepareInstance(Entity *entity);
	};
}

