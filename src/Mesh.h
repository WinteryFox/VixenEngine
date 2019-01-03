#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Material.h"

namespace graphics {
	using namespace std;
	using namespace glm;
	class Mesh {
	private:
		vector<vec3> vertices;
		vector<unsigned int> indices;
		vector<vec2> uvs;
		vector<vec3> normals;
		
		Material *material;
		
		GLuint vao;
		GLuint vertexVBO;
		GLuint indicesVBO;
		GLuint uvsVBO;
		GLuint normalsVBO;
	
	public:
		explicit Mesh(vector<vec3> &vertices, vector<unsigned int> &indices, vector<vec2> &uvs, vector<vec3> &normals, Material *material);
		~Mesh();
		
		vector<unsigned int> getIndices() const;
		
		vector<vec3> getVertices() const;
		
		Material* getMaterial() const;
		
		GLuint getVao() const;
		
		GLuint getVertexVBO() const;
		
		GLuint getIndicesVBO() const;
		
		GLuint getUvsVBO() const;
		
		GLuint getNormalsVBO() const;
		
		bool isVisible() const;
		
		void setVisible(bool visible);
	
	private:
		void generateBuffers();
		void deleteBuffers();
	};
}

