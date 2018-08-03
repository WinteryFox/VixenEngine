#include "Light.h"

namespace graphics {
	Light::Light(glm::vec3 position, glm::vec3 color) : position(position), color(color) {
	
	}
	
	const vec3 &Light::getPosition() const {
		return position;
	}
	
	void Light::setPosition(const vec3 &position) {
		Light::position = position;
	}
	
	const vec3 &Light::getColor() const {
		return color;
	}
	
	void Light::setColor(const vec3 &color) {
		Light::color = color;
	}
}