#ifndef VIXENENGINE_IMAGE_H
#define VIXENENGINE_IMAGE_H

#include <GL/glew.h>
#include <png.h>

class Image {
public:
	GLenum format;
	unsigned int width;
	unsigned int height;
	png_byte* data;
	
	Image(GLenum format, unsigned int width, unsigned int height, png_byte* data) : format(format), width(width), height(height), data(data) {};
	~Image() {
		delete data;
	}
};

#endif