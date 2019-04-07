#include <Window.h>
#include <EntityRender.h>

int main() {
    graphics::Window* window = new graphics::Window("Hello!", 1720, 720);
    
    graphics::EntityRender* entityRender = new graphics::EntityRender("../../resources/");
    input::Camera* camera = new input::Camera();
    std::vector<objects::entity::Entity*> entities;
    std::vector<graphics::Light*> lights;
    
    while (!window->shouldClose()) {
        window->update();
        
        entityRender->render(camera, entities, lights);
        
        window->swap();
    }
    
    return 0;
}