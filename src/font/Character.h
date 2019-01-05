#pragma once

#include <glm/vec2.hpp>
#include "../Texture.h"

namespace font {
	class Character {
	public:
		graphics::Texture* texture;
		glm::vec2 size;
		glm::vec2 offset;
		long advance;
		
		Character(graphics::Texture *texture, const glm::vec2 &size, const glm::vec2 &offset, long advance);
	};
}