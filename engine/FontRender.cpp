#include <set>
#include "FontRender.h"

namespace graphics {
	void FontRender::render(graphics::Window *window, std::map<font::Font *, std::vector<font::Text *>> texts) {
		if (!texts.empty()) {
			shader->start();
			glActiveTexture(GL_TEXTURE0);
			prepare();
			for (const auto &pair : texts) {
				glBindTexture(GL_TEXTURE_2D, pair.first->texture->id);
				for (font::Text *text : pair.second) {
					prepareInstance(window, text);
					glDrawElements(GL_TRIANGLES, text->indicesCount, GL_UNSIGNED_INT, nullptr);
				}
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glBindVertexArray(0);
			shader->stop();
			
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		}
	}
	
	void FontRender::prepare() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
	}
	
	void FontRender::prepareInstance(graphics::Window *window, const font::Text *text) {
		glBindVertexArray(text->vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, text->verticesVBO);
		glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, text->uvsVBO);
		glEnableVertexAttribArray(1);
		
		glm::vec2 size = window->getSize();
		shader->loadPosition(text->position.x, size.y - text->position.y - text->boundingBox.y);
		shader->loadColor(text->color);
		shader->loadProjection(glm::ortho(0.0f, size.x, 0.0f, size.y));
	}
}