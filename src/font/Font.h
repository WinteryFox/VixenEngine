#pragma once

#include <map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../Texture.h"

extern std::string resourcePath;

namespace font {
	struct Character {
		graphics::Texture* texture;
		glm::vec2 size;
		glm::vec2 offset;
		long advance;
	};
	class Font {
	private:
		std::map<char, Character> characters;
		
		void loadFont(const std::string &file);
		
	public:
		explicit Font(const std::string &file);
		
	};
}