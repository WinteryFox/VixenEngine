#ifndef VIXENENGINE_MATERIAL_H
#define VIXENENGINE_MATERIAL_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace graphics {
	using namespace glm;
	class Material {
	private:
		GLuint texture = 0;
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
	
	public:
		Material(GLuint texture, vec3 ambient, vec3 diffuse, vec3 specular, float shininess) : texture(texture), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}
		Material() {}
		~Material() {
			glDeleteTextures(1, &texture);
		}
		
		GLuint getTexture() const;
		
		void setTexture(GLuint texture);
		
		const vec3 &getAmbient() const;
		
		void setAmbient(const vec3 &ambient);
		
		const vec3 &getDiffuse() const;
		
		void setDiffuse(const vec3 &diffuse);
		
		const vec3 &getSpecular() const;
		
		void setSpecular(const vec3 &specular);
		
		float getShininess() const;
		
		void setShininess(float shininess);;
	};
}

#endif