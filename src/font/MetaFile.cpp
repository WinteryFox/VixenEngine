#include "MetaFile.h"

namespace font {
	MetaFile::MetaFile(std::string file) {
		file = resourcePath + "fonts/" + file;
		this->aspectRatio = (double) 16 / (double) 9;
		stream = std::ifstream(file, std::ios::in);
		if (stream.is_open()) {
			loadPaddingData();
			loadLineSize();
			int imageWidth = getValue("scaleW");
			loadCharacterData(imageWidth);
			stream.close();
		} else {
			std::cout << "Failed to open font file: " << file << std::endl;
			delete this;
		}
	}
	
	bool MetaFile::processNextLine() {
		values.clear();
		std::string line;
		if (getline(stream, line)) {
			size_t pos = 0;
			std::string token;
			std::string value;
			std::vector<std::string> parts;
			while ((pos = line.find(SPLITTER)) != std::string::npos) {
				token = line.substr(0, pos);
				parts.push_back(token);
				line.erase(0, pos + 1);
			}
			
			for (std::string &part : parts) {
				std::vector<std::string> valuePairs;
				while ((pos = part.find('=')) != std::string::npos) {
					size_t length = part.size();
					token = part.substr(0, pos);
					value = part.substr(pos + 1, length);
					valuePairs.push_back(token);
					valuePairs.push_back(value);
					part.erase(0, pos + 1);
				}
				if (valuePairs.size() == 2) {
					values.emplace(valuePairs[0], valuePairs[1]);
				}
			}
		} else {
			return false;
		}
		return true;
	}
	
	void MetaFile::loadPaddingData() {
		processNextLine();
		this->padding = getValues("padding");
		this->paddingWidth = padding[PAD_LEFT] + padding[PAD_RIGHT];
		this->paddingHeight = padding[PAD_TOP] + padding[PAD_BOTTOM];
	}
	
	void MetaFile::loadLineSize() {
		processNextLine();
		int lineHeight = getValue("lineHeight") - paddingHeight;
		verticalPixelSize = LINE_HEIGHT - paddingHeight;
		horizontalPixelSize = verticalPixelSize / aspectRatio;
	}
	
	Character* MetaFile::loadCharacter(int imageSize) {
		unsigned int id = getValue("id");
		if (id == SPACE_ASCII) {
			this->spaceWidth = (getValue("xadvance") - paddingWidth) * horizontalPixelSize;
			return nullptr;
		}
		double xTex = ((double) getValue("x") + (padding[PAD_LEFT] - PADDING)) / imageSize;
		double yTex = ((double) getValue("y") + (padding[PAD_TOP] - PADDING)) / imageSize;
		int width = getValue("width") - (paddingWidth - (2 * PADDING));
		int height = getValue("height") - ((paddingHeight) - (2 * PADDING));
		double quadWidth = width * horizontalPixelSize;
		double quadHeight = height * verticalPixelSize;
		double xTexSize = (double) width / imageSize;
		double yTexSize = (double) height / imageSize;
		double xOff = (getValue("xoffset") + padding[PAD_LEFT] - PADDING) * horizontalPixelSize;
		double yOff = (getValue("yoffset") + (padding[PAD_TOP] - PADDING)) * horizontalPixelSize;
		double xAdvance = (getValue("xadvance") - paddingWidth) * horizontalPixelSize;
		return new Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
	}
	
	void MetaFile::loadCharacterData(int width) {
		processNextLine();
		processNextLine();
		while (processNextLine()) {
			Character* character = loadCharacter(width);
			if (character != nullptr) {
				metadata.emplace(character->id, character);
			}
		}
	}
	
	std::vector<unsigned int> MetaFile::getValues(std::string key) {
		std::vector<std::string> numbers;
		std::string value = values.find(key)->second;
		
		size_t pos;
		std::string token;
		while ((pos = value.find(NUMBER_SEPARATOR)) != std::string::npos) {
			token = value.substr(0, pos);
			numbers.push_back(token);
			value.erase(0, pos + 1);
		}
		numbers.push_back(value);
		
		std::vector<unsigned int> values(numbers.size());
		for (const auto &number : numbers) {
			values.push_back((unsigned int) std::stoi(number));
		}
		return values;
	}
	
	unsigned int MetaFile::getValue(std::string key) {
		return (unsigned int) std::stoi(values.find(key)->second);
	}
	
	Character *MetaFile::getCharacter(unsigned int ascii) {
		return metadata.find(ascii)->second;
	}
}