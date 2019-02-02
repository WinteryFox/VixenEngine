#include "Generator.h"

namespace terrain {
	terrain::Chunk *Generator::flatChunk(int gridX, int gridZ, int size, int maxVertices) {
		vector<vec3> vertices;
		vector<unsigned int> indices;
		vector<vec2> uvs;
		vector<vec3> normals;
		std::vector<glm::vec3> tangents;
		std::vector<glm::vec3> bitangents;
		
		for (unsigned int i = 0; i < maxVertices; i++) {
			for (unsigned int j = 0; j < maxVertices; j++) {
				vertices.emplace_back(
						(float) j / ((float) maxVertices - 1) * size,
						0,
						(float) i / ((float) maxVertices - 1) * size);
				uvs.emplace_back(
						(float) j / ((float) maxVertices - 1) * 2,
						(float) i / ((float) maxVertices - 1) * 2);
				normals.emplace_back(0, 1, 0);
			}
		}
		
		for(unsigned int gz = 0; gz < maxVertices - 1; gz++) {
			for(unsigned int gx = 0; gx < maxVertices - 1; gx++) {
				unsigned int topLeft = (gz * maxVertices) + gx;
				unsigned int topRight = topLeft + 1;
				unsigned int bottomLeft = ((gz + 1) * maxVertices) + gx;
				unsigned int bottomRight = bottomLeft + 1;
				indices.push_back(topLeft);
				indices.push_back(bottomLeft);
				indices.push_back(topRight);
				indices.push_back(topRight);
				indices.push_back(bottomLeft);
				indices.push_back(bottomRight);
			}
		}
		graphics::loader::Loader::calculateTangentSpace(vertices, uvs, indices, tangents, bitangents);
		
		return new terrain::Chunk(
				new graphics::Mesh(vertices, indices, uvs, normals, tangents, bitangents,
				                   new graphics::Material(
						                   vec3(0.05f, 0.05f, 0.05f), vec3(1, 1, 1), vec3(0, 0, 0), 50,
						                   graphics::loader::Loader::generateTexture("textures/wall/wall.png"),
						                   graphics::loader::Loader::generateTexture("textures/wall/wall_normal.png"))),
				size, gridX, gridZ, 0);
	}
}