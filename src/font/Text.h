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
		int size;
		glm::vec3 color = glm::vec3(0.0f);
		Font* font;
		
	private:
		std::string text;
		GLuint vao, vbo;
		std::vector<glm::vec2> vertices;
		
	public:
		Text(const std::string &text, const glm::vec2 &position, int size, Font *font);
		void setText(const std::string &text);
		
	private:
		void updateBuffer();
	};
}