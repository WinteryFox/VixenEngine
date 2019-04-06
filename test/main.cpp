#ifdef __APPLE__

#include <mach-o/dyld.h>
#include <sys/proc_info.h>
#include <libproc.h>
#include <zconf.h>

#endif
#include <Window.h>
#include <render/MasterRender.h>

std::string resourcePath;

int main() {
#ifdef __WIN32__
	resourcePath = "../../resources/";
#elif __APPLE__
	char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
	
	proc_pidpath(getpid(), pathbuf, sizeof(pathbuf));
	resourcePath =
			std::string(pathbuf).substr(0, std::string(pathbuf).find_last_of('/')) + std::string("/../../resources/");
#endif
    
    auto *window = new graphics::Window("Vixen Engine", 1280, 720);
    auto *camera = new input::Camera(glm::vec3(0.0f, 2.0f, 5.0f));
    auto *render = new graphics::MasterRender();
	
	render->addEntity("models/tree/tree.dae");
	
	render->addPointTemperatureLight(glm::vec3(3.0f, 3.0f, 5.0f), 5000, 0.0007, 0.00001, 1.0);
	//render->addDirectionalTemperatureLight(glm::vec3(-0.3f, -0.7f, -0.3f), 20000);
	
	render->addTerrain(0, 0);
	render->addTerrain(0, -1);
	render->addTerrain(-1, -1);
	render->addTerrain(-1, 0);
	
	while (!window->shouldClose()) {
		render->render(window, camera);
	}
	
	delete render;
	delete camera;
	delete window;
	
	return 0;
}