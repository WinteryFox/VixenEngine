#include "Mesh.h"

namespace graphics {
	Mesh::Mesh(const vector<vec3> &vertices, const vector<unsigned int> &indices, const vector<vec2> &uvs,
	           const vector<vec3> &normals, const vector<vec3> &tangents, const vector<vec3> &bitangents,
	           Material *material) : vertexCount(vertices.size()),
	                                 indicesCount(indices.size()),
	                                 uvCount(uvs.size()),
	                                 normalCount(normals.size()),
	                                 material(material),
	                                 tangentCount(tangents.size()),
	                                 bitangentCount(bitangents.size()) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vertexVBO);
		glGenBuffers(1, &indicesVBO);
		glGenBuffers(1, &uvsVBO);
		glGenBuffers(1, &normalsVBO);
		glGenBuffers(1, &tangentsVBO);
		glGenBuffers(1, &biTangentsVBO);
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		glBindBuffer(GL_ARRAY_BUFFER, tangentsVBO);
		glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(vec3), &tangents[0], GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		glBindBuffer(GL_ARRAY_BUFFER, biTangentsVBO);
		glBufferData(GL_ARRAY_BUFFER, bitangents.size() * sizeof(vec3), &bitangents[0], GL_STATIC_DRAW);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		glBindVertexArray(0);
	}
	
	Mesh::~Mesh() {
		glDeleteBuffers(1, &indicesVBO);
		glDeleteBuffers(1, &uvsVBO);
		glDeleteBuffers(1, &vertexVBO);
		glDeleteBuffers(1, &normalsVBO);
		glDeleteBuffers(1, &tangentsVBO);
		glDeleteBuffers(1, &biTangentsVBO);
		glDeleteVertexArrays(1, &vao);
	}
}