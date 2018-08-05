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
		Light(vec3 position, vec3 color);
		
		const vec3 &getDirection() const;
		
		void setDirection(const vec3 &direction);
		
		const vec3 &getColor() const;
		
		void setColor(const vec3 &color);
	};
}

#endif