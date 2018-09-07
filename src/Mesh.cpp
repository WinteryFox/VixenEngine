#include "Mesh.h"

namespace graphics::model {
	Mesh::Mesh(vector<vec3> &vertices, vector<unsigned int> &indices, vector<vec2> &uvs, vector<vec3> &normals, Material *material) : vertices(vertices), indices(indices) ,uvs(uvs), normals(normals), material(material) {
		generateBuffers();
	}
	
	Mesh::~Mesh() {
		deleteBuffers();
	}
	
	void Mesh::generateBuffers() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		glGenBuffers(1, &vertexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices.data()[0], GL_STATIC_DRAW);
		
		glGenBuffers(1, &indicesVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.data()[0], GL_STATIC_DRAW);
		
		glGenBuffers(1, &uvsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs.data()[0], GL_STATIC_DRAW);
		
		glGenBuffers(1, &normalsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals.data()[0], GL_STATIC_DRAW);
		
		glBindVertexArray(0);
	}
	
	void Mesh::deleteBuffers() {
		glDeleteBuffers(1, &indicesVBO);
		glDeleteBuffers(1, &vertexVBO);
		glDeleteBuffers(1, &normalsVBO);
		glDeleteVertexArrays(1, &vao);
	}
	
	GLuint Mesh::getVao() const {
		return vao;
	}
	
	GLuint Mesh::getVertexVBO() const {
		return vertexVBO;
	}
	
	GLuint Mesh::getIndicesVBO() const {
		return indicesVBO;
	}
	
	GLuint Mesh::getUvsVBO() const {
		return uvsVBO;
	}
	
	GLuint Mesh::getNormalsVBO() const {
		return normalsVBO;
	}
	
	vector<unsigned int> Mesh::getIndices() const {
		return indices;
	}
	
	vector<vec3> Mesh::getVertices() const {
		return vertices;
	}
	
	Material* Mesh::getMaterial() const {
		return material;
	}
}