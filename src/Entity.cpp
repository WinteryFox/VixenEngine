#include "Entity.h"

namespace objects::entity {
	Entity::Entity(Model* model, vec3 position, vec3 rotation, float scale) : model(model), position(position), scale(scale) {
		this->eulerRotation = rotation;
		this->rotation = quat(rotation);
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
	
	mat4 Entity::getModelMatrix() {
		return mat4(glm::translate(position) * toMat4(rotation) * glm::scale(vec3(scale)));
	}
}