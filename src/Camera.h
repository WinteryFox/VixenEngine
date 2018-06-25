#ifndef VIXENENGINE_CAMERA_H
#define VIXENENGINE_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "Window.h"

namespace input {
	using namespace glm;
	class Camera {
	private:
		bool firstMouse = true;
		double lastX = 0, lastY = 0;
		
		vec3 position;
		float horizontal = 3.14f;
		float vertical = 0.0f;
		float FoV;
		float speed;
		float sensitivity;
		
		mat4 projection;
		mat4 view;
		
	public:
		explicit Camera(vec3 position = vec3(0.0), float FoV = 45.0f, float speed = 0.05f, float sensitivity = 1.0f) : position(position), FoV(FoV), speed(speed), sensitivity(sensitivity) { }
		
		mat4 getProjection();
		mat4 getView();
		
		vec3 getPosition();
		
		void update(graphics::Window *window);
	};
}

#endif