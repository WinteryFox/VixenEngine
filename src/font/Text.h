#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Font.h"

namespace font {
	class Text {
	public:
		std::string text;
		glm::vec2 position;
		Font* font;
		GLuint vao, vbo;
		
		Text(const std::string &text, const glm::vec2 &position, Font *font);
	};
}