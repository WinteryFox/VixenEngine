#pragma once

#include <map>
#include <vector>
#include "../font/Font.h"
#include "../font/Text.h"
#include "../shaders/GuiShader.h"

namespace graphics {
	class FontRender {
	private:
		shaders::GuiShader* shader;
		std::map<font::Font*, std::vector<font::Text*>> texts;
	
	public:
		FontRender() {
			this->shader = new shaders::GuiShader();
		}
		void render();
		void add(font::Text* text);
		
	private:
		void prepare();
		void prepareInstance(const font::Text* text);
	};
}