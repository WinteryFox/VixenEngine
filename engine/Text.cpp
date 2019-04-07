#include "Text.h"

namespace font {
	Text::Text(Font *font, const std::string &text, const glm::vec2 &position, const glm::vec3 &color, float size)
			: text(text),
			  position(position),
			  size(size), color(color), font(font) {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &verticesVBO);
		glGenBuffers(1, &uvsVBO);
		glGenBuffers(1, &indicesVBO);
		
		glBindVertexArray(vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		updateBuffer();
	}
	
	Text::~Text() {
		glDeleteBuffers(1, &indicesVBO);
		glDeleteBuffers(1, &uvsVBO);
		glDeleteBuffers(1, &verticesVBO);
		glDeleteVertexArrays(1, &vao);
	}
	
	void Text::setText(const std::string &text) {
		this->text = text;
		updateBuffer();
	}
	
	void Text::updateBuffer() {
		std::vector<glm::vec2> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;
		
		float cursorX = 0;
		float cursorY = 0;
		float maxX = 0;
		float maxY = 0;
		
		unsigned int offset = 0;
		
		for (char i : text) {
			Character *character = font->characters[i];
			float x = cursorX + character->bitmapDir.x * size;
			float y = -cursorY - character->bitmapDir.y * size;
			float width = character->bitmapSize.x * size;
			float height = character->bitmapSize.y * size;
			
			cursorX += character->advance.x * size;
			cursorY += character->advance.y * size;
			
			maxX += width;
			maxY = std::max(height, maxY);
			
			if (!width || !height)
				continue;
			
			glm::vec2 bottomLeft(x, -y);
			glm::vec2 bottomRight(x + width, -y);
			glm::vec2 topLeft(x, -y - height);
			glm::vec2 topRight(x + width, -y - height);
			
			offset = vertices.size();
			
			vertices.emplace_back(bottomLeft);
			vertices.emplace_back(topLeft);
			vertices.emplace_back(topRight);
			vertices.emplace_back(bottomRight);
			
			indices.emplace_back(offset);
			indices.emplace_back(offset + 1);
			indices.emplace_back(offset + 2);
			
			indices.emplace_back(offset);
			indices.emplace_back(offset + 2);
			indices.emplace_back(offset + 3);
			
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
			
			uvs.emplace_back(bottomLeft);
			uvs.emplace_back(topLeft);
			uvs.emplace_back(topRight);
			uvs.emplace_back(bottomRight);
		}
		boundingBox = glm::vec2(maxX, maxY);
		
		verticesCount = vertices.size();
		uvsCount = uvs.size();
		indicesCount = indices.size();
		
		glBindVertexArray(vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_DYNAMIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}