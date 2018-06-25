#include "Entity.h"

namespace graphics::model {
	Entity::Entity(const Mesh &mesh, vec3 position, vec3 rotation, float scale) : mesh(mesh) {
		this->mesh = mesh;
		this->position = position;
		this->rotation = quat(rotation);
		this->scale = scale;
	}
	
	Mesh *Entity::getMesh() {
		return &mesh;
	}
	
	vec3 Entity::getPosition() {
		return position;
	}
	
	void Entity::setPosition(vec3 position) {
		this->position = position;
	}
	
	quat Entity::getRotation() {
		return rotation;
	}
	
	vec3 Entity::getEulerRotation() {
		return eulerRotation;
	}
	
	void Entity::setRotation(vec3 rotation) {
		this->eulerRotation = rotation;
		this->rotation = quat(rotation);
	}
	
	float Entity::getScale() {
		return scale;
	}
	
	void Entity::setScale(float scale) {
		this->scale = scale;
	}
	
	mat4 Entity::getModelMatrix() {
		return mat4(translate(mat4(), position) * toMat4(rotation) * glm::scale(vec3(scale)));
	}
}