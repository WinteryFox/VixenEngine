#ifndef VIXENENGINE_ENTITY_H
#define VIXENENGINE_ENTITY_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"

namespace graphics::model {
	class Entity {
	private:
		Mesh *mesh;
		vec3 position;
		mat4 rotation;
		vec3 eulerRotation;
		float scale;
		
	public:
		Entity(Mesh *mesh, vec3 position, vec3 rotation, float scale);
		
		Mesh* getMesh();
		void setMesh(Mesh *mesh);
		vec3 getPosition();
		void setPosition(vec3 position);
		mat4 getRotation();
		void setRotation(vec3 rotation);
		vec3 getEulerRotation();
		float getScale();
		void setScale(float scale);
	};
}

#endif