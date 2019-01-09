#include "Light.h"

namespace graphics {
	Light::Type Light::getType() const {
		return type;
	}
	
	void Light::setType(Light::Type type) {
		Light::type = type;
	}
	
	const vec3 &Light::getDirection() const {
		return direction;
	}
	
	void Light::setDirection(const vec3 &direction) {
		Light::direction = direction;
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
	
	float Light::getQuadratic() const {
		return quadratic;
	}
	
	float Light::getLinear() const {
		return linear;
	}
	
	float Light::getConstant() const {
		return constant;
	}
	
	void Light::setDirectional(const vec3 &direction, const vec3 &color) {
		this->type = Type::DIRECTIONAL;
		this->direction = direction;
		this->color = color;
	}
	
	void Light::setAttenuation(const vec3 &position, const vec3 &color, float quadratic, float linear, float constant) {
		this->type = Type::POINT;
		this->position = position;
		this->color = color;
		this->quadratic = quadratic;
		this->linear = linear;
		this->constant = constant;
	}
}