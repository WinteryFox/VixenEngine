#include "Text.h"

namespace font {
	Text::Text(const std::string &text, const glm::vec2 &position, int size, Font *font) : text(text), position(position),
	                                                                             size(size), font(font) {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		updateBuffer();
		/*glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), nullptr);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);*/
	}
	
	void Text::setText(const std::string &text) {
		this->text = text;
		updateBuffer();
	}
	
	void Text::updateBuffer() {
		for (auto ch : text) {
			Character character = font->characters[ch];
			
		}
		glBindVertexArray(vao);
		
	}
}