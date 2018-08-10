#ifndef VIXENENGINE_PLAYER_H
#define VIXENENGINE_PLAYER_H

#include "Camera.h"
#include "Model.h"

namespace controls::Player {
	class Player {
	private:
		const input::Camera camera;
		const graphics::model::Model mesh;
		const float cameraOffset;
		
	public:
		Player(float cameraOffset = 0.0f);
	};
}

#endif