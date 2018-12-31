#include "Entity.h"

namespace objects::entity {
	Entity::Entity(Model* model, vec3 position, vec3 rotation, float scale) : model(model), position(position), scale(scale) {
		this->eulerRotation = rotation;
		this->rotation = quat(rotation);
	}
	
	Model* Entity::getModel() {
		return model;
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
		return mat4(glm::translate(position) * toMat4(rotation) * glm::scale(vec3(scale)));
	}
}