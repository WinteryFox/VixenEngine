#pragma once

#include <map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../Texture.h"
#include "Character.h"

extern std::string resourcePath;

namespace font {
	class Font {
	private:
		void loadFont(const std::string &file);
		
	public:
		std::map<char, Character*> characters;
		unsigned int atlasWidth = 0;
		unsigned int atlasHeight = 0;
		unsigned int maxHeight;
		graphics::Texture* texture;
		
		explicit Font(const std::string &file);
		
	};
}