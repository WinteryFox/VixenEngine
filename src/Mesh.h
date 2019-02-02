#pragma once

#include <vector>
#include <glm/glm.hpp>
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
		const unsigned int tangentCount;
		const unsigned int bitangentCount;
		
		Material* material;
		
		GLuint vao, vertexVBO, uvsVBO, indicesVBO, normalsVBO, tangentsVBO, biTangentsVBO;
		
		explicit Mesh(const vector<vec3> &vertices, const vector<unsigned int> &indices, const vector<vec2> &uvs,
		              const vector<vec3> &normals, const vector<vec3> &tangents, const vector<vec3> &bitangents,
		              Material *material);
		~Mesh();
	};
}

