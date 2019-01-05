#pragma once

#include <vector>
#include "../Mesh.h"
#include "../Entity.h"
#include "../Camera.h"
#include "../Light.h"
#include "../Phong.h"

namespace graphics {
	using namespace objects::entity;
	class Render {
	private:
		shaders::Phong *shader;
		std::vector<Entity*> entities;
		std::vector<graphics::Light*> lights;
	
	public:
		Render() {
			shader = new shaders::Phong();
		}
		void render(input::Camera *camera);
		void add(Entity *entity);
		void addLight(graphics::Light *light);
	
	private:
		void prepareMesh(const Mesh *mesh);
		void prepareInstance(Entity *entity);
	};
}

