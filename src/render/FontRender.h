#pragma once

#include <map>
#include <vector>
#include "../font/FontType.h"
#include "../font/TextMeshData.h"
#include "../font/GuiText.h"
#include "../GuiShader.h"

namespace graphics {
	class FontRender {
	private:
		shaders::GuiShader* shader;
		std::map<font::FontType*, std::vector<font::GuiText*>> texts;
	
	public:
		FontRender() {
			this->shader = new shaders::GuiShader();
		}
		void render();
		void add(font::GuiText* text);
		
	private:
		void prepare(const font::FontType* font);
		void prepareInstance(const font::GuiText* text);
	};
}