#ifndef VIXENENGINE_DIRECTIONALLIGHT_H
#define VIXENENGINE_DIRECTIONALLIGHT_H

#include "glm/glm.hpp"

namespace graphics {
	using namespace glm;
	class Light {
	private:
		vec3 direction;
		vec3 color;
	
	public:
		Light(const vec3 &direction, const vec3 &color);
		
		vec3 getDirection();
		
		void setDirection(const vec3 &direction);
		
		vec3 getColor();
		
		void setColor(const vec3 &color);
	};
}

#endif