#ifndef VIXENENGINE_MESH_H
#define VIXENENGINE_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace graphics::model {
	using namespace std;
	using namespace glm;
	class Mesh {
	private:
		vector<vec3> vertices;
		vector<unsigned int> indices;
		vector<vec2> uvs;
		vector<vec3> normals;
		
		GLuint texture;
		
		GLuint vao;
		GLuint vertexVBO;
		GLuint indicesVBO;
		GLuint uvsVBO;
		GLuint normalsVBO;
	
	public:
		explicit Mesh(vector<vec3> &vertices, vector<unsigned int> &indices, vector<vec2> &uvs, vector<vec3> &normals, GLuint &texture);
		~Mesh();
		
		vector<unsigned int> getIndices() const;
		
		vector<vec3> getVertices() const;
		
		GLuint getTexture() const;
		
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

#endif