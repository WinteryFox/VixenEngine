#include "Camera.h"

namespace input {
	glm::mat4 Camera::getProjection() {
		return projection;
	}
	
	glm::mat4 Camera::getView() {
		return view;
	}
	
	glm::vec3 Camera::getPosition() {
		return position;
	}
	
	void Camera::update(double dt, double tickrate) {
		if (!window->focused())
			return;
		
		GLFWwindow* w = window->window;
		
		double currentX = 0, currentY = 0;
		double xOffset = 0, yOffset = 0;
		glfwGetCursorPos(w, &currentX, &currentY);
		if (firstMouse) {
			lastX = currentX;
			lastY = currentY;
			firstMouse = false;
		}
		xOffset = currentX - lastX;
		yOffset = currentY - lastY;
		lastX = currentX;
		lastY = currentY;
		
		horizontal -= sensitivity * xOffset * dt;
		vertical -= sensitivity * yOffset * dt;

		vertical = glm::clamp(vertical, -1.5f, 1.5f);
		
		vec3 direction(cos(vertical) * sin(horizontal), sin(vertical), cos(vertical) * cos(horizontal));
		vec3 right(sin(horizontal - 3.14f / 2.0f), 0, cos(horizontal - 3.14f / 2.0f));
		vec3 up = cross(right, direction);
		
		auto advance = glm::vec3(0.0f);
		
		if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
			advance += direction * speed;
		if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
			advance -= direction * speed;
		if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
			advance += right * speed;
		if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
			advance -= right * speed;
		if (glfwGetKey(w, GLFW_KEY_SPACE))
			advance += vec3(0, 1, 0) * speed;
		if (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT))
			advance -= vec3(0, 1, 0) * speed;
		if (glfwGetKey(w, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(w, GLFW_TRUE);
		
		advance.x *= tickrate;
		advance.y *= tickrate;
		advance.z *= tickrate;
		position += advance;
		
		glm::vec2 size = window->size();
		projection = perspective(radians(FoV), (float) size.x / (float) size.y, 0.1f, 1000.0f);
		view = lookAt(position, position + direction, up);
	}
}