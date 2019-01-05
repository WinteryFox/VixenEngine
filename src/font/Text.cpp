#include "Text.h"

namespace font {
	Text::Text(const std::string &text, const glm::vec2 &position, int size, Font *font) : text(text), position(position),
	                                                                             size(size), font(font) {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &verticesVBO);
		glGenBuffers(1, &uvsVBO);
		
		glBindVertexArray(vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		updateBuffer();
	}
	
	void Text::setText(const std::string &text) {
		this->text = text;
		updateBuffer();
	}
	
	void Text::updateBuffer() {
		float x = position.x;
		float y = position.y;
		for (auto ch : text) {
			Character* character = font->characters[ch];
			float width = character->size.x * size;
			float height = character->size.y * size;
			
			float xpos = x + character->offset.x * size;
			float ypos = y - (character->size.y - character->offset.y) * size;
			
			vertices.emplace_back(xpos, ypos + height);
			vertices.emplace_back(xpos, ypos);
			vertices.emplace_back(xpos + width, ypos);
			vertices.emplace_back(xpos, ypos + height);
			vertices.emplace_back(xpos + width, ypos);
			vertices.emplace_back(xpos + width, ypos + height);
			
			uvs.emplace_back(0.0f, 0.0f);
			uvs.emplace_back(0.0f, 1.0f);
			uvs.emplace_back(1.0f, 1.0f);
			uvs.emplace_back(0.0f, 0.0f);
			uvs.emplace_back(1.0f, 1.0f);
			uvs.emplace_back(1.0f, 0.0f);
			
			x += (character->advance >> 6) * size;
		}
		
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	std::vector<Character*> Text::getCharacters() {
		std::vector<Character*> characters;
		for (auto c : text) {
			characters.push_back(font->characters[c]);
		}
		return characters;
	}
}