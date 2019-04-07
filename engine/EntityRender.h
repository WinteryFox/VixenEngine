#pragma once

#include <GL/glew.h>
#include <vector>
#include "Phong.h"
#include "Camera.h"
#include "Entity.h"

namespace graphics {
	class EntityRender {
	private:
		shaders::Phong* shader;
	
	public:
		explicit EntityRender(const std::string &resourcePath);
		
		void render(input::Camera* camera, std::vector<objects::entity::Entity *> &entities, std::vector<Light *> &lights);
	
	private:
		void prepareMesh(const Mesh *mesh);
		
		void prepareInstance(objects::entity::Entity *entity);
	};
}

