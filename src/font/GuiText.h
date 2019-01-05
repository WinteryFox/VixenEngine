#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "TextMeshCreator.h"
#include "FontType.h"

namespace font {
	class FontType;
	class GuiText {
	public:
		std::string text;
		float size;
		
		GLuint textMeshVao = 0;
		unsigned int vertexCount = 0;
		glm::vec3 color = glm::vec3(0.0f);
		
		glm::vec2 position;
		float lineMaxSize;
		unsigned int numberOfLines = 0;
		
		bool center = false;
		
		FontType* font;
	
	public:
		GuiText(std::string text, float fontSize, FontType* font, glm::vec2 position, float lineMaxSize, bool center);
	};
}