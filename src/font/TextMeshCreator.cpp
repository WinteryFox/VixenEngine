#include "TextMeshCreator.h"

namespace font {
	TextMeshCreator::TextMeshCreator(const std::string &file) {
		metadata = new MetaFile(file);
	}
	
	TextMeshData* TextMeshCreator::createTextMesh(GuiText* text) {
		std::vector<Line*> lines = createStructure(text);
		TextMeshData* data = createQuadVertices(text, lines);
		return data;
	}
	
	std::vector<Line*> TextMeshCreator::createStructure(GuiText *text) {
		char chars[text->text.size()];
		strcpy(chars, text->text.c_str());
		std::vector<Line*> lines;
		Line* currentLine = new Line(metadata->spaceWidth, text->size, text->lineMaxSize);
		Word* currentWord = new Word(text->size);
		for (char c : chars) {
			auto ascii = (unsigned int) c;
			if (ascii == SPACE_ASCII) {
				if (!currentLine->addWord(currentWord)) {
					lines.push_back(currentLine);
					currentLine = new Line(metadata->spaceWidth, text->size, text->lineMaxSize);
					currentLine->addWord(currentWord);
				}
				currentWord = new Word(text->size);
				continue;
			}
			currentWord->addCharacter(metadata->getCharacter(ascii));
		}
		if (!currentLine->addWord(currentWord)) {
			lines.push_back(currentLine);
			currentLine = new Line(metadata->spaceWidth, text->size, text->lineMaxSize);
			currentLine->addWord(currentWord);
		}
		lines.push_back(currentLine);
		return lines;
	}
	
	TextMeshData* TextMeshCreator::createQuadVertices(GuiText* text, std::vector<Line*> lines) {
		text->numberOfLines = lines.size();
		double cursorX = 0.0f, cursorY = 0.0f;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		
		for (auto line : lines) {
			if (text->center) {
				cursorX = (line->maxLength - line->currentLineLength) / 2;
			}
			for (auto word : line->words) {
				for (auto character : word->characters) {
					addCharacterVertices(cursorX, cursorY, character, text->size, vertices);
					addUV(uvs, character->xCoord, character->yCoord, character->xMaxCoord, character->yMaxCoord);
					cursorX += metadata->spaceWidth * text->size;
				}
				cursorX += metadata->spaceWidth * text->size;
			}
			cursorX = 0;
			cursorY += LINE_HEIGHT * text->size;
		}
		return new TextMeshData(vertices, uvs);
	}
	
	void TextMeshCreator::addCharacterVertices(double cursorX, double cursorY, Character *character, double fontSize,
	                                           std::vector<glm::vec3> &vertices) {
		double x = cursorX + (character->xOffset * fontSize);
		double y = cursorY + (character->yOffset * fontSize);
		double maxX = x + (character->sizeX * fontSize);
		double maxY = y + (character->sizeY * fontSize);
		double properX = (2 * x) - 1;
		double properY = (-2 * y) + 1;
		double properMaxX = (2 * maxX) - 1;
		double properMaxY = (-2 * maxY) + 1;
		addVertices(vertices, properX, properY, properMaxX, properMaxY);
	}
	
	void TextMeshCreator::addVertices(std::vector<glm::vec3> &vertices, double x, double y, double maxX, double maxY) {
		vertices.emplace_back((float) x);
		vertices.emplace_back((float) y);
		vertices.emplace_back((float) x);
		vertices.emplace_back((float) maxY);
		vertices.emplace_back((float) maxX);
		vertices.emplace_back((float) maxY);
		vertices.emplace_back((float) maxX);
		vertices.emplace_back((float) maxY);
		vertices.emplace_back((float) maxX);
		vertices.emplace_back((float) y);
		vertices.emplace_back((float) x);
		vertices.emplace_back((float) y);
	}
	
	void TextMeshCreator::addUV(std::vector<glm::vec2> &uvs, double x, double y, double maxX, double maxY) {
		uvs.emplace_back((float) x);
		uvs.emplace_back((float) y);
		uvs.emplace_back((float) x);
		uvs.emplace_back((float) maxY);
		uvs.emplace_back((float) maxX);
		uvs.emplace_back((float) maxY);
		uvs.emplace_back((float) maxX);
		uvs.emplace_back((float) maxY);
		uvs.emplace_back((float) maxX);
		uvs.emplace_back((float) y);
		uvs.emplace_back((float) x);
		uvs.emplace_back((float) y);
	}
}