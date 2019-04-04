#pragma once

#include "glm/glm.hpp"

namespace graphics {
	using namespace glm;
	class Light {
	public:
		enum Type {
			DIRECTIONAL = 0,
			POINT = 1,
		};
		
		explicit Light(Type type) : type(type) { }
		
		Type type;
		vec3 direction{};
		
		vec3 position{};
		dvec3 color{};
		unsigned int temperature;
		
		float quadratic{};
		float linear{};
		float constant{};
		
	public:
		void setAttenuation(const vec3 &position, const vec3 &color, float quadratic, float linear, float constant);
		void setDirectional(const vec3 &direction, const vec3 &color);
		
		void setTemperature(unsigned int kelvin);
	};
}

