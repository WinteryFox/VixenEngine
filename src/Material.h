#ifndef VIXENENGINE_MATERIAL_H
#define VIXENENGINE_MATERIAL_H

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include "Texture.h"

namespace graphics {
	using namespace glm;
	class Material {
	public:
		Texture* texture;
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
		
		Material(Texture* texture, vec3 ambient, vec3 diffuse, vec3 specular, float shininess) : texture(texture), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}
	};
}

#endif