#pragma once

#include "GuiText.h"
#include "TextMeshCreator.h"
#include "TextMeshData.h"
#include "../Loader.h"
#include "../Texture.h"

namespace font {
	class GuiText;
	class TextMeshCreator;
	class FontType {
	public:
		TextMeshCreator* creator;
		graphics::Texture* texture;
		
		explicit FontType(const std::string &file);
		
		TextMeshData* loadText(GuiText* text);
	};
}