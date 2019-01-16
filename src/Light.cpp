#include <iostream>
#include "Light.h"

namespace graphics {
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
	
	void Light::setTemperature(unsigned int kelvin) {
		if (kelvin < 1000)
			kelvin = 1000;
		if (kelvin > 40000)
			kelvin = 40000;
		
		temperature = kelvin;
		
		double r, g, b;
		
		kelvin /= 100;
		
		if (kelvin <= 66) {
			r = 255;
		} else {
			r = kelvin - 60;
			r = 329.698727446 * std::pow(r, -0.1332047592);
			
			if (r < 0)
				r = 0;
			if (r > 255)
				r = 255;
		}
		
		if (kelvin <= 66) {
			g = kelvin;
			g = 99.4708025861 * std::log(g) - 161.1195681661;
		} else {
			g = kelvin - 60;
			g = 288.1221695283 * std::pow(g, -0.0755148492);
		}
		
		if (g < 0)
			g = 0;
		if (g > 255)
			g = 255;
		
		if (kelvin >= 66) {
			b = 255;
		} else {
			if (kelvin <= 19) {
				b = 0;
			} else {
				b = kelvin - 10;
				b = 138.5177312231 * std::log(b) - 305.0447927307;
			}
		}
		
		if (b < 0)
			b = 0;
		if (b > 255)
			b = 255;
		
		r /= 255;
		g /= 255;
		b /= 255;
		color = glm::dvec3(r, g, b);
	}
}