#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "Character.h"

extern std::string resourcePath;

namespace font {
	class MetaFile {
	public:
		const unsigned int PAD_TOP = 0;
		const unsigned int PAD_LEFT = 1;
		const unsigned int PAD_BOTTOM = 2;
		const unsigned int PAD_RIGHT = 3;
		
		const unsigned int PADDING = 3;
		
		const unsigned char SPLITTER = ' ';
		const unsigned char NUMBER_SEPARATOR = ',';
		
		const float LINE_HEIGHT = 0.03f;
		const unsigned int SPACE_ASCII = 32;
		
		double aspectRatio;
		
		double verticalPixelSize;
		double horizontalPixelSize;
		double spaceWidth;
		std::vector<unsigned int> padding;
		unsigned int paddingWidth;
		unsigned int paddingHeight;
		std::map<unsigned int, Character*> metadata;
		std::map<std::string, std::string> values;
		
		std::ifstream stream;
		
		bool processNextLine();
		void loadPaddingData();
		void loadLineSize();
		Character* loadCharacter(int imageSize);
		void loadCharacterData(int width);
		std::vector<unsigned int> getValues(std::string key);
		unsigned int getValue(std::string key);
		
	public:
		explicit MetaFile(std::string file);
		
		Character* getCharacter(unsigned int ascii);
		
	};
}