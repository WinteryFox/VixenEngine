#include "MasterRender.h"

namespace graphics {
    MasterRender::MasterRender() {
        resourcePath = "../../resources/";
        
        entityRender = new EntityRender(resourcePath);
        fontRender = new FontRender(resourcePath);
        terrainRender = new TerrainRender(resourcePath);
        
        arial = new font::Font("arial.ttf", 14);
        fpsText = new font::Text(arial, "FPS: 0");
        vertexText = new font::Text(arial, "Vertices: 0", glm::vec2(0.0f, fpsText->boundingBox.y));
        gpuText = new font::Text(arial, std::string("GPU: ") +
                                        reinterpret_cast<const char *>(glGetString(GL_RENDERER)) + std::string(" ") +
                                        reinterpret_cast<const char *>(glGetString(GL_VERSION)),
                                 vec2(0.0f, vertexText->position.y + vertexText->boundingBox.y));
        
        texts[arial].push_back(fpsText);
        texts[arial].push_back(vertexText);
        texts[arial].push_back(gpuText);
    }
    
    MasterRender::~MasterRender() {
        delete arial;
        delete fpsText;
        delete vertexText;
        delete gpuText;
        
        delete entityRender;
        delete fontRender;
        delete terrainRender;
    }
    
    void MasterRender::render(graphics::Window *window, input::Camera *camera) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        window->update();
        
        double newFrame = glfwGetTime();
        double frameTime = newFrame - lastFrame;
        lastFrame = newFrame;
        
        accumulator += frameTime;
        
        while (accumulator >= tickrate) {
            camera->update(window, frameTime, tickrate);
            accumulator -= tickrate;
            // TODO: Fix this.
        }
        
        entityRender->render(camera, entities, lights);
        terrainRender->render(camera, chunks, lights);
        fontRender->render(window, texts);
        
        fps++;
        double currentTime = glfwGetTime();
        if (currentTime - lastTime >= 1.0) {
            fpsText->setText("FPS: " + std::to_string(fps));
            fps = 0;
            lastTime = currentTime;
        }
        
        window->swap();
    }
    
    objects::entity::Entity *MasterRender::addEntity(const std::string &file, vec3 position, vec3 rotation, float scale) {
        model::Model *model = graphics::loader::Loader::loadModel(file);
        auto *entity = new objects::entity::Entity(model, position, rotation, scale);
        
        for (Mesh *mesh : model->getMeshes()) {
            vertices += mesh->vertexCount;
        }
        
        vertexText->setText("Vertices: " + std::to_string(vertices));
        entities.push_back(entity);
        return entity;
    }
    
    objects::entity::Entity *MasterRender::addEntity(Mesh *mesh, vec3 position, vec3 rotation, float scale) {
        std::vector<graphics::Mesh *> meshes = {mesh};
        auto *entity = new objects::entity::Entity(new model::Model(meshes), position, rotation, scale);
        
        vertices += mesh->vertexCount;
        
        vertexText->setText("Vertices: " + std::to_string(vertices));
        entities.push_back(entity);
        return entity;
    }
    
    objects::entity::Entity *MasterRender::addEntity(model::Model *model, vec3 position, vec3 rotation, float scale) {
        auto *entity = new objects::entity::Entity(model, position, rotation, scale);
        
        for (Mesh *mesh : model->getMeshes()) {
            vertices += mesh->vertexCount;
        }
        
        vertexText->setText("Vertices: " + std::to_string(vertices));
        entities.push_back(entity);
        return entity;
    }
    
    terrain::Chunk *MasterRender::addTerrain(int gridX, int gridZ) {
        terrain::Chunk *chunk = terrain::Generator::flatChunk(gridX, gridZ);
        vertices += chunk->mesh->vertexCount;
        vertexText->setText("Vertices: " + std::to_string(vertices));
        chunks.push_back(chunk);
        return chunk;
    }
    
    graphics::Light *MasterRender::addDirectionalLight(const vec3 &direction, const dvec3 &color) {
        auto light = new graphics::Light(graphics::Light::Type::DIRECTIONAL);
        light->setDirectional(direction, color);
        lights.emplace_back(light);
        return light;
    }
    
    graphics::Light *MasterRender::addDirectionalTemperatureLight(const vec3 &direction, unsigned int temperature) {
        auto light = new graphics::Light(graphics::Light::Type::DIRECTIONAL);
        light->direction = direction;
        light->setTemperature(temperature);
        lights.emplace_back(light);
        return light;
    }
    
    graphics::Light *
    MasterRender::addPointLight(const vec3 &position, const dvec3 &color, float quadratic, float linear,
                                float constant) {
        auto light = new graphics::Light(graphics::Light::Type::POINT);
        light->setAttenuation(position, color, quadratic, linear, constant);
        lights.emplace_back(light);
        return light;
    }
    
    graphics::Light *
    MasterRender::addPointTemperatureLight(const vec3 &position, unsigned int temperature, float quadratic,
                                           float linear,
                                           float constant) {
        auto light = new graphics::Light(graphics::Light::Type::POINT);
        light->position = position;
        light->setTemperature(temperature);
        light->quadratic = quadratic;
        light->linear = linear;
        light->constant = constant;
        lights.emplace_back(light);
        return light;
    }
}