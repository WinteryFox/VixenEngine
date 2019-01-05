#pragma once

#include <utility>
#include <vector>
#include <glm/glm.hpp>

namespace font {
	class TextMeshData {
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> coords;
		
		TextMeshData(std::vector<glm::vec3> vertices, std::vector<glm::vec2> coords);
		
		unsigned int getVertexCount();
	};
}