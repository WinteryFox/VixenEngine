#include "Window.h"
#include "render/MasterRender.h"

std::string resourcePath = "../resources/";
graphics::Window* window = new graphics::Window("Vixen Engine", 1280, 720);
input::Camera *camera = new input::Camera(glm::vec3(0.0f, 2.0f, 5.0f));
graphics::MasterRender* render = new graphics::MasterRender();

int main() {
	render->addEntity("models/tree/tree.dae");
	render->addDirectionalTemperatureLight(glm::vec3(-0.5f), 20000);
	//render->addPointLight(glm::vec3(-1.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	
	while (!window->shouldClose()) {
		render->render();
	}
	
	delete render;
	delete camera;
	delete window;
	
	return 0;
}