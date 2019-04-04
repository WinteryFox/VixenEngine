#pragma once

#include <GL/glew.h>
#include <vector>
#include "../Mesh.h"
#include "../Entity.h"
#include "../Camera.h"
#include "../Light.h"
#include "../shaders/Phong.h"
#include "../font/Text.h"

namespace graphics {
	using namespace objects::entity;
	class EntityRender {
	private:
		shaders::Phong* shader;
	
	public:
		explicit EntityRender(const std::string &resourcePath) {
			shader = new shaders::Phong(resourcePath);
		}
		
		void render(input::Camera* camera, std::vector<Entity *> &entities, std::vector<Light *> &lights);
	
	private:
		void prepareMesh(const Mesh *mesh);
		
		void prepareInstance(Entity *entity);
	};
}

