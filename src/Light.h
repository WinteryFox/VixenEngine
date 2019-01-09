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
	
	private:
		Type type;
		vec3 direction{};
		
		vec3 position{};
		vec3 color{};
		
		float quadratic{};
		float linear{};
		float constant{};
		
	public:
		Type getType() const;
		
		void setType(Type type);
		
		const vec3 &getDirection() const;
		
		void setDirection(const vec3 &direction);
		
		const vec3 &getPosition() const;
		
		void setPosition(const vec3 &position);
		
		const vec3 &getColor() const;
		
		float getQuadratic() const;
		
		float getLinear() const;
		
		float getConstant() const;
		
		void setAttenuation(const vec3 &position, const vec3 &color, float quadratic, float linear, float constant);
		
		void setDirectional(const vec3 &direction, const vec3 &color);
	};
}

