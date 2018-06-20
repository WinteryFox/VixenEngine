#include "Entity.h"

namespace graphics::model {
	Entity::Entity(Mesh *mesh, vec3 position, vec3 rotation, float scale) : mesh(mesh), position(position), eulerRotation(rotation), scale(scale){
	
	}
	
	void Entity::setMesh(Mesh *mesh) {
		this->mesh = mesh;
	}
	
	vec3 Entity::getPosition() {
		return position;
	}
	
	void Entity::setPosition(vec3 position) {
		this->position = position;
	}
	
	mat4 Entity::getRotation() {
		return rotation;
	}
	
	vec3 Entity::getEulerRotation() {
		return eulerRotation;
	}
	
	void Entity::setRotation(vec3 rotation) {
		this->eulerRotation = rotation;
		this->rotation = toMat4(quat(rotation));
	}
	
	float Entity::getScale() {
		return scale;
	}
	
	void Entity::setScale(float scale) {
		this->scale = scale;
	}
	
	Mesh* Entity::getMesh() {
		return mesh;
	}
}