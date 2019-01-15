
#include "Window.h"
#include "render/MasterRender.h"

std::string resourcePath = "../resources/";
graphics::Window* window = new graphics::Window("Vixen Engine", 1280, 720);
input::Camera* camera = new input::Camera();
graphics::MasterRender* render = new graphics::MasterRender();

int main() {
	render->addEntity("models/kizuna/kizuna.dae");
	render->addDirectionalLight(glm::vec3(-0.5f));
	render->addPointLight(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	while (!window->shouldClose()) {
		render->render();
	}
	
	delete render;
	delete camera;
	delete window;
	
	return 0;
}