#include <set>
#include "FontRender.h"
#include "../Window.h"

namespace graphics {
	void FontRender::render() {
		shader->start();
		glActiveTexture(GL_TEXTURE0);
		prepare();
		for (auto text : texts) {
			prepareInstance(text);
			std::vector<font::Character*> characters = text->getCharacters();
			for (int i = 0; i < characters.size(); i++) {
				glBindTexture(GL_TEXTURE_2D, characters[i]->texture->id);
				glDrawArrays(GL_TRIANGLES, i * 6, 6);
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
	
	void FontRender::prepare() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
	}
	
	void FontRender::prepareInstance(const font::Text *text) {
		glBindVertexArray(text->vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, text->verticesVBO);
		glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, text->uvsVBO);
		glEnableVertexAttribArray(1);
		
		shader->loadColor(text->color);
		shader->loadProjection(glm::ortho(0.0f, (float) graphics::Window::WIDTH, 0.0f, (float) graphics::Window::HEIGHT));
	}
	
	void FontRender::add(font::Text* text) {
		texts.push_back(text);
	}
}