#pragma once

#include <glm/vec3.hpp>
#include <iostream>
#include "Texture.h"

namespace graphics {
	using namespace glm;
	
	class Material {
	public:
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
		Texture *tDiffuse;
		Texture *tNormal;
		
		Material(const vec3 &ambient, const vec3 &diffuse, const vec3 &specular, float shininess, Texture *tDiffuse,
		         Texture *tNormal = new Texture(0)) : ambient(ambient),
		                                              diffuse(diffuse),
		                                              specular(specular),
		                                              shininess(shininess),
		                                              tDiffuse(tDiffuse),
		                                              tNormal(tNormal) {
			
		}
		
		explicit Material(Texture *tDiffuse,
		                  Texture *tNormal = new Texture(0),
		                  const vec3 &ambient = vec3(0.1), const vec3 &diffuse = vec3(1.0),
		                  const vec3 &specular = vec3(0.1), const float &shininess = 50.0f) : ambient(ambient),
		                                                                                      diffuse(diffuse),
		                                                                                      specular(specular),
		                                                                                      shininess(shininess),
		                                                                                      tDiffuse(tDiffuse),
		                                                                                      tNormal(tNormal) {
			
		}
		
		~Material() {
			delete tDiffuse;
			delete tNormal;
		}
	};
}

