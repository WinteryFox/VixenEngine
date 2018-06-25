#ifndef VIXENENGINE_MESHRENDER_H
#define VIXENENGINE_MESHRENDER_H

#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Entity.h"
#include "Camera.h"

namespace graphics::model {
	class Render {
	private:
		graphics::shaders::Shader *shader;
		std::vector<Entity*> entities;
	
	public:
		void render(input::Camera *camera);
		void use(graphics::shaders::Shader *shader);
		void add(Entity *entity);
	
	private:
		void prepareMesh(Mesh *mesh);
		void prepareInstance(Entity *entity);
	};
}

#endif