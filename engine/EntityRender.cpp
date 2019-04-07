#include "EntityRender.h"

namespace graphics {
	EntityRender::EntityRender(const std::string &resourcePath) {
		shader = new shaders::Phong("../resources/");
	}
	
	void EntityRender::render(input::Camera* camera, std::vector<objects::entity::Entity *> &entities, std::vector<Light *> &lights) {
		if (!entities.empty()) {
			//shader->start();
			
			//shader->loadProjectionMatrix(camera->getProjection());
			//shader->loadViewMatrix(camera->getView());
			
			//shader->loadViewPosition(camera->getPosition());
			
			//shader->loadLights(lights);
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			
			for (auto *entity : entities) {
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
			
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
			
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(3);
			glDisableVertexAttribArray(4);
			glBindVertexArray(0);
			//shader->stop();
		}
	}
	
	void EntityRender::prepareInstance(objects::entity::Entity *entity) {
		//shader->loadModelMatrix(entity->getModelMatrix());
	}
	
	void EntityRender::prepareMesh(const Mesh *mesh) {
		glBindVertexArray(mesh->vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		
		//shader->loadMaterial(mesh->material);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->material->tDiffuse->id);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mesh->material->tNormal->id);
	}
}