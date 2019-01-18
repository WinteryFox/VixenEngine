#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "../Window.h"
#include "Font.h"

extern graphics::Window* window;

namespace font {
	class Text {
	public:
		glm::vec2 position;
		float size;
		glm::vec3 color;
		Font* font;
		glm::vec2 boundingBox;
		unsigned int verticesCount, uvsCount, indicesCount;
		GLuint vao, verticesVBO, uvsVBO, indicesVBO;
		
	private:
		std::string text;
		
	public:
		Text(Font *font, const std::string &text, const glm::vec2 &position = glm::vec3(0.0f),
		      const glm::vec3 &color = glm::vec3(1.0f), float size = 1.0f);
		~Text();
		
		void setText(const std::string &text);
		
	private:
		void updateBuffer();
	};
}