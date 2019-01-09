#include "EntityRender.h"

namespace graphics {
	void EntityRender::render(std::vector<Entity*> &entities, std::vector<Light*> &lights) {
		shader->start();
		
		shader->loadProjectionMatrix(camera->getProjection());
		shader->loadViewMatrix(camera->getView());
		
		shader->loadViewPosition(camera->getPosition());
		
		shader->loadLights(lights);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		
		for (auto &entity : entities) {
			if (entity->model->isVisible()) {
				prepareInstance(entity);
				for (auto *mesh : entity->model->getMeshes()) {
					prepareMesh(mesh);
					glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);
				}
			}
		}
		
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
		shader->stop();
	}
	
	void EntityRender::prepareInstance(Entity *entity) {
		shader->loadModelMatrix(entity->getModelMatrix());
	}
	
	void EntityRender::prepareMesh(const Mesh *mesh) {
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
		
		shader->loadMaterial(mesh->getMaterial());
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->getMaterial()->texture->id);
	}
}