#pragma once

#include <iostream>
#ifndef __unix__
#include <GL/glew.h>
#else
#include <GL/gl.h>
#endif

namespace graphics {
	class Texture {
	public:
		GLuint id;
		
		explicit Texture(GLuint id) : id(id) { }
		
		~Texture() {
			glDeleteTextures(1, &id);
		}
	};
}

