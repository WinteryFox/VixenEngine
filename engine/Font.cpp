#include <iostream>
#include "Font.h"

namespace font {
	Font::Font(const std::string &file, unsigned int fontSize) : fontSize(fontSize) {
		loadFont("../../resources/fonts/" + file);
	}
	
	void Font::loadFont(const std::string &file) {
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			std::cerr << "Could not init FreeType" << std::endl;
			delete this;
		}
		FT_Face font;
		if (FT_New_Face(ft, file.c_str(), 0, &font)) {
			std::cerr << "Could not load font: " << file.c_str() << std::endl;
			delete this;
		}
		
		FT_Set_Pixel_Sizes(font, 0, fontSize);
		
		unsigned int rowWidth = 0;
		unsigned int rowHeight = 0;
		
		FT_GlyphSlot glyph = font->glyph;
		
		for (GLubyte i = 32; i < 128; i++) {
			if (FT_Load_Char(font, i, FT_LOAD_RENDER)) {
				std::cerr << "Failed to load glyph: " << i << std::endl;
				continue;
			}
			
			if (rowWidth + glyph->bitmap.width + 1 >= 1024) {
				atlasWidth = std::max(atlasWidth, rowWidth);
				atlasHeight += rowHeight;
				rowWidth = 0;
				rowHeight = 0;
			}
			
			rowWidth += glyph->bitmap.width + 1;
			rowHeight = std::max(rowHeight, glyph->bitmap.rows);
			maxHeight = std::max(maxHeight, rowHeight);
		}
		
		atlasWidth = std::max(atlasWidth, rowWidth);
		atlasHeight += rowHeight;
		
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlasWidth, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		int xOffset = 0;
		int yOffset = 0;
		rowHeight = 0;
		
		for (GLubyte i = 32; i < 128; i++) {
			if (FT_Load_Char(font, i, FT_LOAD_RENDER)) {
				std::cerr << "Failed to load character: " << i << std::endl;
				continue;
			}
			
			if (xOffset + glyph->bitmap.width + 1 >= 1024) {
				yOffset += rowHeight;
				rowHeight = 0;
				xOffset = 0;
			}
			
			glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, glyph->bitmap.width, glyph->bitmap.rows, GL_RED,
			                GL_UNSIGNED_BYTE, glyph->bitmap.buffer);
			
			characters.insert(std::pair<char, Character *>(i, new Character(
					glm::vec2(glyph->advance.x >> 6, glyph->advance.y >> 6),
					glm::vec2(glyph->bitmap.width, glyph->bitmap.rows),
					glm::vec2(glyph->bitmap_left, glyph->bitmap_top),
					glm::vec2(xOffset, yOffset))));
			
			rowHeight = std::max(rowHeight, glyph->bitmap.rows);
			xOffset += glyph->bitmap.width + 1;
		}
		this->texture = new graphics::Texture(texture);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		
		FT_Done_Face(font);
		FT_Done_FreeType(ft);
	}
}