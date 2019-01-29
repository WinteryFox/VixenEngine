#pragma once

#include "../Loader.h"
#include "EntityRender.h"
#include "FontRender.h"
#include "TerrainRender.h"
#include "../Generator.h"
#include "../Chunk.h"

namespace graphics {
	class MasterRender {
	private:
		EntityRender *entityRender;
		FontRender *fontRender;
		TerrainRender *terrainRender;
		
		unsigned int vertices = 0;
		
		unsigned int fps = 0;
		double lastTime;
		
		const double tickrate = 1.0 / 128.0;
		double lastFrame = glfwGetTime();
		double accumulator = 0.0;
		
		font::Font *arial;
		font::Text *fpsText;
		font::Text *vertexText;
		font::Text *gpuText;
		
		std::vector<Entity *> entities;
		std::vector<graphics::Light *> lights;
		std::map<font::Font *, std::vector<font::Text *>> texts;
		std::vector<terrain::Chunk*> chunks;
		
	public:
		MasterRender();
		~MasterRender();
		
		void render();
		
		Entity *
		addEntity(const std::string &file, vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), float scale = 1.0f);
		
		Entity *addEntity(Mesh *mesh, vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), float scale = 1.0f);
		//void addText(const std::string text, const std::string font, );
		terrain::Chunk *addTerrain(int gridX, int gridZ);
		
		graphics::Light *
		addDirectionalLight(const vec3 &direction = vec3(0.0f, -0.5f, 0.0f), const dvec3 &color = dvec3(1.0f));
		
		graphics::Light *addDirectionalTemperatureLight(const vec3 &direction = vec3(0.0f, -0.5f, 0.0f),
		                                                unsigned int temperature = 40000);
		
		graphics::Light *addPointLight(const vec3 &position, const dvec3 &color = dvec3(0.0f), float quadratic = 0.002f,
		                               float linear = 0.07f, float constant = 1.0f);
		
		graphics::Light *
		addPointTemperatureLight(const vec3 &position, unsigned int temperature = 40000, float quadratic = 0.002f,
		                         float linear = 0.07f, float constant = 1.0f);
	};
}