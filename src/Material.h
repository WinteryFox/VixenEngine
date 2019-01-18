#pragma once

#include <glm/vec3.hpp>
#include <iostream>
#include "Texture.h"

namespace graphics {
	using namespace glm;
	
	class Material {
	public:
		Texture *texture;
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
		
		Material(Texture *texture, vec3 ambient, vec3 diffuse, vec3 specular, float shininess) : texture(texture),
		                                                                                         ambient(ambient),
		                                                                                         diffuse(diffuse),
		                                                                                         specular(specular),
		                                                                                         shininess(shininess) {
			
		}
		
		~Material() {
			delete texture;
		}
	};
}

