#pragma once

#include <map>
#include <vector>
#include "Font.h"
#include "Text.h"
#include "GuiShader.h"

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