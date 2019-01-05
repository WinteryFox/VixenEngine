#include "GuiText.h"

namespace font {
	GuiText::GuiText(std::string text, float size, FontType* font, glm::vec2 position, float lineMaxSize, bool center) : text(std::move(text)), size(size), position(position),
	lineMaxSize(lineMaxSize), font(font), center(center) {
		TextMeshData* data = font->loadText(this);
		
		GLuint vao, posVBO, texVBO;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		glGenBuffers(1, &posVBO);
		glBindBuffer(GL_ARRAY_BUFFER, posVBO);
		glBufferData(GL_ARRAY_BUFFER, data->vertices.size() * sizeof(glm::vec3), &data->vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glGenBuffers(1, &texVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texVBO);
		glBufferData(GL_ARRAY_BUFFER, data->coords.size() * sizeof(glm::vec2), &data->coords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindVertexArray(0);
		
		textMeshVao = vao;
		vertexCount = data->getVertexCount();
	}
}