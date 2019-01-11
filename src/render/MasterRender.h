#pragma once

#include "../Loader.h"
#include "EntityRender.h"
#include "FontRender.h"
#include "TerrainRender.h"
#include "../Generator.h"

namespace graphics {
	class MasterRender {
	private:
		EntityRender* entityRender;
		
		unsigned int vertices = 0;
		
		std::vector<Entity> entities;
		std::vector<graphics::Light> lights;
		std::vector<font::Text> texts;
		std::vector<graphics::Mesh*> terrains;
		
	public:
		MasterRender();
		
		void render();
		
		void addEntity(const std::string &file, vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), float scale = 1.0f);
		//void addText(const std::string text, const std::string font, );
		void addTerrain(int gridX, int gridZ);
		void addDirectionalLight(vec3 direction = vec3(0.0f, -0.5f, 0.0f), vec3 color = vec3(1.0f));
		void addPointLight(vec3 position, vec3 color = vec3(0.0f), float quadratic = 0.02f, float linear = 0.7f, float constant = 1.0f);
	};
}