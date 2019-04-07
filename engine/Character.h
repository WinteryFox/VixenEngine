#pragma once

#include <glm/vec2.hpp>
#include "Texture.h"

namespace font {
	class Character {
	public:
		glm::vec2 advance;
		glm::vec2 bitmapSize;
		glm::vec2 bitmapDir;
		glm::vec2 texture;
		
		Character(const glm::vec2 &advance, const glm::vec2 &bitmapSize, const glm::vec2 &bitmapDir,
		          const glm::vec2 &texture) : advance(advance), bitmapSize(bitmapSize), bitmapDir(bitmapDir),
		                                     texture(texture) {}
	};
}