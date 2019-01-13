
#include "Window.h"
#include "render/MasterRender.h"

std::string resourcePath = "../resources/";
graphics::Window* window = new graphics::Window("Vixen Engine", 1280, 720);
input::Camera* camera = new input::Camera();
graphics::MasterRender* render = new graphics::MasterRender();

int main() {
	/*
	auto* render = new graphics::EntityRender();
	
	auto* light = new graphics::Light(graphics::Light::Type::POINT);
	light->setAttenuation(glm::vec3(0.0f, 2.0f, 3.0f), glm::vec3(1.0, 1.0, 1.0), 0.002f, 0.07, 1.0f);
	render->addLight(light);
	
	graphics::model::Model* model = graphics::loader::Loader::loadModel("models/kizuna/kizuna.dae");
	render->add(new objects::entity::Entity(model));
	render->add(new objects::entity::Entity(model, glm::vec3(1.0f), glm::vec3(0), 0.5f));
	
	auto* generator = new terrain::Generator();
	auto* chunk = new terrain::Chunk(generator->flatChunk(), 0, 0, 0);
	
	std::vector<graphics::Mesh*> meshes;
	meshes.push_back(chunk->mesh);
	render->add(new objects::entity::Entity(new graphics::Model(meshes), glm::vec3(0), glm::vec3(0), 1.0f));
	
	auto* fontRender = new graphics::FontRender();
	font::Text* fps = new font::Text("FPS: 0", glm::vec2(0.0f), 1.0f, arial);
	font::Text* vertices = new font::Text("Verts: 0", glm::vec2(0.0f, 8 / graphics::Window::WIDTH), 1.0f, arial);
	fps->color = glm::vec3(0.9f, 0.768f, 1.0f);
	vertices->color = glm::vec3(0.9f, 0.768f, 1.0f);
	fontRender->add(fps);
	fontRender->add(vertices);*/
	
	//double lastFPS = 0;
	//int iFPS = 0;
	
	render->addEntity("models/kizuna/kizuna.dae");
	render->addDirectionalLight(glm::vec3(-0.5f));
	
	while (!window->shouldClose()) {
		window->update();
		
		render->render();
		
		window->swap();
		
		/*iFPS++;
		double currentTime = glfwGetTime();
		double FPSTime = currentTime - lastFPS;
		if (FPSTime >= 1.0) {
			fps->setText("FPS: " + std::to_string(iFPS));
			iFPS = 0;
			lastFPS = currentTime;
		}*/
	}
	
	delete render;
	delete camera;
	delete window;
	
	return 0;
}