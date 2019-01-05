#include <iostream>
#include "Font.h"

namespace font {
	Font::Font(const std::string &file) {
		loadFont(file);
	}
	
	void Font::loadFont(const std::string &file) {
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			std::cout<< "Could not init FreeType" << std::endl;
			delete this;
		}
		FT_Face font;
		if (FT_New_Face(ft, (resourcePath + "fonts/" + file).c_str(), 0, &font)) {
			std::cout << "Could not load font" << std::endl;
			delete this;
		}
		
		FT_Set_Pixel_Sizes(font, 0, 48);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		for (GLubyte c = 0; c < 128; c++) {
			if (FT_Load_Char(font, c, FT_LOAD_RENDER)) {
				std::cout << "Failed to load glyph: " << c << std::endl;
				continue;
			}
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, font->glyph->bitmap.width, font->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, font->glyph->bitmap.buffer);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			
			characters.insert(std::pair<char, Character*>(c, new Character(new graphics::Texture(texture),
			                                                               glm::vec2(font->glyph->bitmap.width, font->glyph->bitmap.rows),
			                                                               glm::vec2(font->glyph->bitmap_left, font->glyph->bitmap_top),
			                                                               font->glyph->advance.x)));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		
		FT_Done_Face(font);
		FT_Done_FreeType(ft);
	}
}