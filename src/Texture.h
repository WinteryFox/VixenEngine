#pragma once

#include <GL/glew.h>

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

