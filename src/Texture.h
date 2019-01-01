#ifndef VIXENENGINE_TEXTURE_H
#define VIXENENGINE_TEXTURE_H

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

#endif