#include "Render.h"

namespace graphics::model {
	void Render::render(input::Camera *camera) {
		shader->start();
		
		shader->loadProjectionMatrix(camera->getProjection());
		shader->loadViewMatrix(camera->getView());
		
		for (auto &entity : entities) {
			prepareInstance(entity);
			prepareMesh(entity->getMesh());
			glDrawElements(GL_TRIANGLES, entity->getMesh()->getIndices().size(), GL_UNSIGNED_INT, nullptr);
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		shader->stop();
	}
	
	void Render::prepareInstance(graphics::model::Entity *entity) {
		shader->loadModelMatrix(entity->getModelMatrix());
	}
	
	void Render::prepareMesh(Mesh *mesh) {
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
	
	void Render::use(graphics::shaders::Shader *shader) {
		this->shader = shader;
	}
	
	void Render::add(Entity *entity) {
		entities.push_back(entity);
	}
}