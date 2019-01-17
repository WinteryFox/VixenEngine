#include "EntityRender.h"

namespace graphics {
	void EntityRender::render(std::vector<Entity *> &entities, std::vector<Light *> &lights) {
		if (!entities.empty()) {
			shader->start();
			
			shader->loadProjectionMatrix(camera->getProjection());
			shader->loadViewMatrix(camera->getView());
			
			shader->loadViewPosition(camera->getPosition());
			
			shader->loadLights(lights);
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			
			for (auto &entity : entities) {
				prepareInstance(entity);
				for (auto *mesh : entity->model->getMeshes()) {
					prepareMesh(mesh);
					glDrawElements(GL_TRIANGLES, mesh->indicesCount, GL_UNSIGNED_INT, nullptr);
				}
			}
			
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindVertexArray(0);
			shader->stop();
		}
	}
	
	void EntityRender::prepareInstance(Entity *entity) {
		shader->loadModelMatrix(entity->getModelMatrix());
	}
	
	void EntityRender::prepareMesh(const Mesh *mesh) {
		glBindVertexArray(mesh->vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		
		shader->loadMaterial(mesh->material);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->material->texture->id);
	}
}