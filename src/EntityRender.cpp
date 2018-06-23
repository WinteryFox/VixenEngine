#include "EntityRender.h"

namespace graphics::model {
	
	void EntityRender::render() {
		shader->start();
		
		// TODO: Load matrices
		
		for (auto &entity : entities) {
			prepare(entity->getMesh());
			glDrawElements(GL_TRIANGLES, entity->getMesh()->getIndices().size(), GL_UNSIGNED_INT, nullptr);
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		shader->stop();
	}
	
	void EntityRender::prepare(Mesh *mesh) {
		glBindVertexArray(mesh->getVao());
		
		glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexVBO());
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndicesVBO());
		
		glBindBuffer(GL_ARRAY_BUFFER, mesh->getUvsVBO());
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, mesh->getNormalsVBO());
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	
	void EntityRender::use(graphics::shaders::Shader *shader) {
		this->shader = shader;
	}
	
	void EntityRender::add(Entity *entity) {
		entities.push_back(entity);
	}
}