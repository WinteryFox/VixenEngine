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
	
	public:
		FontRender(const std::string &resourcePath) {
			this->shader = new shaders::GuiShader(resourcePath);
		}
		
		void render(graphics::Window *window, std::map<font::Font *, std::vector<font::Text *>> texts);
		
	private:
		void prepare();
		void prepareInstance(graphics::Window *window, const font::Text* text);
	};
}