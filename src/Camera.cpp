#include "Camera.h"

namespace input {
	glm::mat4 Camera::getProjectionMatrix() {
		return projectionMatrix;
	}
	
	glm::mat4 Camera::getViewMatrix() {
		return viewMatrix;
	}
	
	glm::vec3 Camera::getPosition() {
		return position;
	}
	
	void Camera::update(double xOffset, double yOffset) {
	
	}
}