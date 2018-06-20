#ifndef VIXENENGINE_CAMERA_H
#define VIXENENGINE_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

namespace input {
	using namespace glm;
	class Camera {
	private:
		bool firstMouse = true;
		double lastX = 0, lastY = 0;
		
		vec3 position = vec3(0.0);
		float horizontal = 3.14f;
		float vertical = 0.0f;
		float FoV = 45.0f;
		float speed = 50.0f;
		float sensitivity = 1.0f;
		
		mat4 projectionMatrix;
		mat4 viewMatrix;
		
	public:
		explicit Camera(vec3 position = vec3(0.0f), float FoV = 45.0f, float speed = 50.0f, float sensitivity = 1.0f) : position(position), FoV(FoV), speed(speed), sensitivity(sensitivity) { }
		
		mat4 getProjectionMatrix();
		mat4 getViewMatrix();
		
		vec3 getPosition();
		
	protected:
		void update(double xOffset, double yOffset);
	};
}

#endif