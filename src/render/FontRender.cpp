#include <set>
#include "FontRender.h"
#include "../Window.h"

namespace graphics {
	void FontRender::render() {
		shader->start();
		glActiveTexture(GL_TEXTURE0);
		prepare();
		for (const auto &pair : texts) {
			glBindTexture(GL_TEXTURE_2D, pair.first->texture->id);
			for (font::Text* text : pair.second) {
				prepareInstance(text);
				glDrawArrays(GL_TRIANGLES, 0, text->vertices.size());
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
		if (texts.find(text->font)->first == nullptr)
			texts.insert(std::pair<font::Font*, std::vector<font::Text*>>(text->font, std::vector<font::Text*>()));
		texts[text->font].push_back(text);
	}
}