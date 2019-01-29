#include "TerrainRender.h"

namespace graphics {
	TerrainRender::TerrainRender() {
		this->shader = new shaders::Phong();
	}
	
	TerrainRender::~TerrainRender() {
		delete shader;
	}
	
	void TerrainRender::render(std::vector<terrain::Chunk *> chunks, std::vector<graphics::Light*> lights) {
		if (!chunks.empty()) {
			shader->start();
			
			shader->loadProjectionMatrix(camera->getProjection());
			shader->loadViewMatrix(camera->getView());
			
			shader->loadViewPosition(camera->getPosition());
			
			shader->loadLights(lights);
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			
			for (auto &chunk : chunks) {
				prepareInstance(chunk);
				prepareMesh(chunk->mesh);
				glDrawElements(GL_TRIANGLES, chunk->mesh->indicesCount, GL_UNSIGNED_INT, nullptr);
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
	
	void TerrainRender::prepareInstance(terrain::Chunk *chunk) {
		shader->loadModelMatrix(glm::mat4(glm::translate(glm::vec3(chunk->gridX * chunk->size, 0.0, chunk->gridZ * chunk->size)) * glm::toMat4(glm::quat(glm::vec3(0.0f))) * glm::scale(glm::vec3(1.0f))));
	}
	
	void TerrainRender::prepareMesh(Mesh *mesh) {
		glBindVertexArray(mesh->vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		
		shader->loadMaterial(mesh->material);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->material->tDiffuse->id);
	}
}