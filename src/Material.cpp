#include "Material.h"

namespace graphics {
	GLuint Material::getTexture() const {
		return texture;
	}
	
	void Material::setTexture(GLuint texture) {
		Material::texture = texture;
	}
	
	const vec3 &Material::getAmbient() const {
		return ambient;
	}
	
	void Material::setAmbient(const vec3 &ambient) {
		Material::ambient = ambient;
	}
	
	const vec3 &Material::getDiffuse() const {
		return diffuse;
	}
	
	void Material::setDiffuse(const vec3 &diffuse) {
		Material::diffuse = diffuse;
	}
	
	const vec3 &Material::getSpecular() const {
		return specular;
	}
	
	void Material::setSpecular(const vec3 &specular) {
		Material::specular = specular;
	}
	
	float Material::getShininess() const {
		return shininess;
	}
	
	void Material::setShininess(float shininess) {
		Material::shininess = shininess;
	}
}