#include "Character.h"

namespace font {
	Character::Character(graphics::Texture *texture, const glm::vec2 &size, const glm::vec2 &offset, long advance)
			: texture(texture), size(size), offset(offset), advance(advance) {}
}