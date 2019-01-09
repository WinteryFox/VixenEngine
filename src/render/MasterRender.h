#pragma once

#include "EntityRender.h"
#include "FontRender.h"
#include "TerrainRender.h"

namespace graphics {
	class MasterRender {
	private:
		EntityRender* entityRender;
		
		unsigned int vertices = 0;
		unsigned int triangles = 0;
		
		std::vector<Entity*> entities;
		std::vector<graphics::Light*> lights;
		std::vector<font::Text*> texts;
		
	public:
		MasterRender();
		
		void render();
		
		void addEntity(const std::string &file, vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), float scale = 1.0f);
		void addText(font::Text* text);
		void addDirectionalLight(vec3 direction, vec3 color);
		void addPointLight(vec3 position, vec3 color, float quadratic, float linear, float constant);
	};
}