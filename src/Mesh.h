#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Material.h"

namespace graphics {
	using namespace std;
	using namespace glm;
	class Mesh {
	public:
		const unsigned int vertexCount;
		const unsigned int indicesCount;
		const unsigned int uvCount;
		const unsigned int normalCount;
		
		Material material;
		
		GLuint vao;
		GLuint vertexVBO;
		GLuint indicesVBO;
		GLuint uvsVBO;
		GLuint normalsVBO;
		
		explicit Mesh(const vector<vec3> &vertices, const vector<unsigned int> &indices, const vector<vec2> &uvs,
		              const vector<vec3> &normals, const Material &material);
		~Mesh();
	};
}

