#include "FontType.h"

namespace font {
	FontType::FontType(const std::string &file) : texture(graphics::loader::Loader::generateTexture(
			graphics::loader::Loader::loadImage("fonts/" + file.substr(0, file.find_last_of('.')) + ".png"))),
	                                              creator(new TextMeshCreator(file)) {
		
	}
	
	TextMeshData *FontType::loadText(GuiText *text) {
		return creator->createTextMesh(text);
	}
}