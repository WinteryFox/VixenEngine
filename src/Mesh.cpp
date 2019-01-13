#include "Mesh.h"

namespace graphics {
	Mesh::Mesh(const vector<vec3> &vertices, const vector<unsigned int> &indices, const vector<vec2> &uvs,
	           const vector<vec3> &normals, const Material &material) : vertexCount(vertices.size()),
	                                                                    indicesCount(indices.size()),
	                                                                    uvCount(uvs.size()),
	                                                                    normalCount(normals.size()),
	                                                                    material(material) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		glGenBuffers(1, &vertexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glGenBuffers(1, &indicesVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		
		glGenBuffers(1, &uvsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glGenBuffers(1, &normalsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindVertexArray(0);
	}
	
	Mesh::~Mesh() {
		glDeleteBuffers(1, &indicesVBO);
		glDeleteBuffers(1, &vertexVBO);
		glDeleteBuffers(1, &normalsVBO);
		glDeleteVertexArrays(1, &vao);
	}
}