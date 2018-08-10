#ifndef VIXENENGINE_ENTITY_H
#define VIXENENGINE_ENTITY_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

namespace objects::entity {
	using namespace glm;
	using namespace graphics::model;
	class Entity {
	private:
		Model model;
		vec3 position;
		quat rotation;
		vec3 eulerRotation;
		float scale;
		
	public:
		explicit Entity(Model model, vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), float scale = 1.0f);
		
		Model* getModel();
		vec3 getPosition();
		void setPosition(vec3 position);
		quat getRotation();
		void setRotation(vec3 rotation);
		vec3 getEulerRotation();
		float getScale();
		void setScale(float scale);
		mat4 getModelMatrix();
	};
}

#endif