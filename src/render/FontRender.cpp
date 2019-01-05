#include <set>
#include "FontRender.h"

namespace graphics {
	void FontRender::render() {
		shader->start();
		glActiveTexture(GL_TEXTURE0);
		for (auto &iterator : texts) {
			prepare(iterator.first);
			for (font::GuiText* text : iterator.second) {
				prepareInstance(text);
				glDrawArrays(GL_TRIANGLES, 0, text->vertexCount);
			}
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
		shader->stop();
		
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
	
	void FontRender::prepare(const font::FontType* font) {
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, font->texture->id);
	}
	
	void FontRender::prepareInstance(const font::GuiText *text) {
		glBindVertexArray(text->textMeshVao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		shader->loadColor(text->color);
		shader->loadPosition(text->position);
	}
	
	void FontRender::add(font::GuiText* text) {
		texts[text->font].push_back(text);
	}
}