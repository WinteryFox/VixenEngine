#include "MasterRender.h"

namespace graphics {
	MasterRender::MasterRender() {
		camera = input::Camera();
		entityRender = EntityRender();
	}
	
	void MasterRender::render() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		camera.update();
		
		entityRender.render();
	}
}