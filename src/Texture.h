#pragma once

#include <iostream>

#ifdef __WIN32__
#include <GL/glew.h>
#elif __APPLE__

#include <OpenGL/gl.h>

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

