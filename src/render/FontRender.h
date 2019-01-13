#pragma once

#include <map>
#include <vector>
#include "../font/Font.h"
#include "../font/Text.h"
#include "../shaders/GuiShader.h"

extern graphics::Window* window;

namespace graphics {
	class FontRender {
	private:
		shaders::GuiShader* shader;
	
	public:
		FontRender() {
			this->shader = new shaders::GuiShader();
		}
		
		void render(std::map<font::Font *, std::vector<font::Text *>> texts);
		
	private:
		void prepare();
		void prepareInstance(const font::Text* text);
	};
}