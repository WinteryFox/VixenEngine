#pragma once

#ifdef __WIN32__
#include <GL/glew.h>
#elif __APPLE__

#include <OpenGL/gl.h>

#endif
#include <vector>
#include "../Mesh.h"
#include "../Entity.h"
#include "../Camera.h"
#include "../Light.h"
#include "../shaders/Phong.h"
#include "../font/Text.h"

extern input::Camera* camera;

namespace graphics {
	using namespace objects::entity;
	class EntityRender {
	private:
		shaders::Phong* shader;
	
	public:
		EntityRender() {
			shader = new shaders::Phong();
		}
		
		void render(std::vector<Entity *> &entities, std::vector<Light *> &lights);
	
	private:
		void prepareMesh(const Mesh *mesh);
		
		void prepareInstance(Entity *entity);
	};
}

