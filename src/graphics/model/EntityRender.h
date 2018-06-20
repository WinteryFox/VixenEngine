#ifndef VIXENENGINE_MESHRENDER_H
#define VIXENENGINE_MESHRENDER_H

#include <vector>
#include "Mesh.h"
#include "../shaders/Shader.h"
#include "Entity.h"

namespace graphics::model {
	class EntityRender {
	private:
		graphics::shaders::Shader *shader;
		std::vector<Entity*> entities;
	
	public:
		void render();
		void use(graphics::shaders::Shader *shader);
		void add(Entity *entity);
	
	private:
		void prepare(Mesh *mesh);
	};
}

#endif