#include "Light.h"

namespace graphics {
	Light::Light(glm::vec3 direction, glm::vec3 color) : direction(direction), color(color) {
	
	}
	
	const vec3 &Light::getDirection() const {
		return direction;
	}
	
	void Light::setDirection(const vec3 &direction) {
		Light::direction = direction;
	}
	
	const vec3 &Light::getColor() const {
		return color;
	}
	
	void Light::setColor(const vec3 &color) {
		Light::color = color;
	}
}