#pragma once

#include <vector>
#include "../Mesh.h"
#include "../Entity.h"
#include "../Camera.h"
#include "../Light.h"
#include "../shaders/Phong.h"
#include "Render.h"

extern input::Camera camera;

namespace graphics {
	using namespace objects::entity;
	class EntityRender {
	private:
		std::vector<Entity*> entities;
		std::vector<graphics::Light*> lights;
		shaders::Phong shader;
	
	public:
		EntityRender() {
			shader = shaders::Phong();
		}
		void render();
		void add(Entity *entity);
		void addLight(graphics::Light *light);
	
	private:
		void prepareMesh(const Mesh *mesh);
		void prepareInstance(Entity *entity);
	};
}

