#pragma once

#include "FontType.h"
#include "GuiText.h"
#include "MetaFile.h"
#include "TextMeshData.h"
#include "Line.h"

namespace font {
	class GuiText;
	class TextMeshCreator {
	private:
		const float LINE_HEIGHT = 0.03f;
		const unsigned int SPACE_ASCII = 32;
		
		MetaFile* metadata;
		
	public:
		explicit TextMeshCreator(const std::string &file);
		
		TextMeshData* createTextMesh(GuiText* text);
		TextMeshData* createQuadVertices(GuiText* text, std::vector<Line*> lines);
		
	private:
		void addCharacterVertices(double cursorX, double cursorY, Character* character, double fontSize, std::vector<glm::vec3> &vertices);
		void addVertices(std::vector<glm::vec3> &vertices, double x, double y, double maxX, double maxY);
		void addUV(std::vector<glm::vec2> &uvs, double x, double y, double maxX, double maxY);
		
	private:
		std::vector<Line*> createStructure(GuiText* text);
	};
}