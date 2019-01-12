#include "Text.h"

namespace font {
	Text::Text(Font *font, const std::string &text, const glm::vec2 &position, const glm::vec3 &color, float size)
			: text(text),
			  position(position),
			  size(size), color(color), font(font) {
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
		glBindVertexArray(0);
		
		updateBuffer();
	}
	
	void Text::setText(const std::string &text) {
		this->text = text;
		updateBuffer();
	}
	
	void Text::updateBuffer() {
		vertices.clear();
		uvs.clear();
		
		float cursorX = position.x * graphics::Window::WIDTH;
		float cursorY = graphics::Window::HEIGHT - std::round(position.y * graphics::Window::HEIGHT) - font->maxHeight;
		
		for (auto chars : text) {
			Character *character = font->characters[chars];
			float x = cursorX + character->bitmapDir.x * size;
			float y = -cursorY - character->bitmapDir.y * size;
			float width = character->bitmapSize.x * size;
			float height = character->bitmapSize.y * size;
			
			cursorX += character->advance.x * size;
			cursorY += character->advance.y * size;
			
			if (!width || !height)
				continue;
			
			glm::vec2 bottomLeft(x, -y);
			glm::vec2 bottomRight(x + width, -y);
			glm::vec2 topLeft(x, -y - height);
			glm::vec2 topRight(x + width, -y - height);
			
			vertices.emplace_back(topRight);
			vertices.emplace_back(bottomRight);
			vertices.emplace_back(bottomLeft);
			
			vertices.emplace_back(bottomLeft);
			vertices.emplace_back(topLeft);
			vertices.emplace_back(topRight);
			
			glm::vec2 t = character->texture;
			glm::vec2 s = character->bitmapSize;
			glm::vec2 a = glm::vec2(font->atlasWidth, font->atlasHeight);
			
			bottomLeft = glm::vec2(t.x / a.x,
									t.y / a.y);
			bottomRight = glm::vec2((t.x + s.x) / a.x,
									t.y / a.y);
			topLeft = glm::vec2(t.x / a.x,
			                    (t.y + s.y) / a.y);
			topRight = glm::vec2((t.x + s.x) / a.x,
			                     (t.y + s.y) / a.y);
			
			uvs.emplace_back(topRight);
			uvs.emplace_back(bottomRight);
			uvs.emplace_back(bottomLeft);
			
			uvs.emplace_back(bottomLeft);
			uvs.emplace_back(topLeft);
			uvs.emplace_back(topRight);
		}
		
		glBindVertexArray(vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_DYNAMIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	std::vector<Character *> Text::getCharacters() {
		std::vector<Character *> characters;
		for (auto c : text) {
			characters.push_back(font->characters[c]);
		}
		return characters;
	}
	
	glm::vec2 Text::getBoundingBox() {
		return glm::vec2(vertices[vertices.size()].x, font->maxHeight);
	}
}