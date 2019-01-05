#include "TextMeshData.h"

namespace font {
	TextMeshData::TextMeshData(std::vector<glm::vec3> vertices, std::vector<glm::vec2> coords) : vertices(
			std::move(vertices)), coords(
			std::move(coords)) {
		
	}
	
	unsigned int TextMeshData::getVertexCount() {
		return vertices.size() / 2;
	}
}