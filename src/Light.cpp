#include "Light.h"

namespace graphics {
	Light::Light(const vec3 &direction, const vec3 &color) : direction(direction), color(color) {
	
	}
	
	vec3 Light::getDirection() {
		return direction;
	}
	
	void Light::setDirection(const vec3 &direction) {
		Light::direction = direction;
	}
	
	vec3 Light::getColor() {
		return color;
	}
	
	void Light::setColor(const vec3 &color) {
		Light::color = color;
	}
}