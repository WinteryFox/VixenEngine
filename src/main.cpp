#include "Window.h"
#include "render/MasterRender.h"

std::string resourcePath = "../resources/";
graphics::Window *window = new graphics::Window("Vixen Engine", 1280, 720);
input::Camera *camera = new input::Camera(glm::vec3(0.0f, 2.0f, 5.0f));
graphics::MasterRender *render = new graphics::MasterRender();

int main() {
	render->addEntity("models/tree/tree.dae");
	render->addDirectionalTemperatureLight(glm::vec3(-0.5f, -0.5f, -0.5f), 5000);
	
	render->addTerrain(0, 0);
	render->addTerrain(0, -1);
	render->addTerrain(-1, -1);
	render->addTerrain(-1, 0);
	
	while (!window->shouldClose()) {
		render->render();
	}
	
	delete render;
	delete camera;
	delete window;
	
	return 0;
}