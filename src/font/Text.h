#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Font.h"

namespace font {
	class Text {
	public:
		glm::vec2 position;
		float size;
		glm::vec3 color = glm::vec3(0.0f);
		Font* font;
		std::vector<glm::vec2> vertices, uvs;
		GLuint vao, verticesVBO, uvsVBO;
		
	private:
		std::string text;
		
	public:
		Text(const std::string &text, const glm::vec2 &position, float size, Font *font);
		void setText(const std::string &text);
		std::vector<Character*> getCharacters();
		
	private:
		void updateBuffer();
	};
}