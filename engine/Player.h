#pragma once

#include "Camera.h"
#include "Model.h"

namespace controls::Player {
	class Player {
	private:
		const graphics::model::Model mesh;
		const float cameraOffset;
		
	public:
		Player(float cameraOffset = 0.0f);
	};
}

