#pragma once

#include <GL/glew.h>
#include <png.h>

namespace graphics {
	class Image {
	public:
		GLenum format;
		unsigned int width;
		unsigned int height;
		char *data;
		
		Image(GLenum format, unsigned int width, unsigned int height, char *data) : format(format), width(width),
		                                                                                height(height), data(data) {};
		
		~Image() {
			delete[] data;
		}
	};
}