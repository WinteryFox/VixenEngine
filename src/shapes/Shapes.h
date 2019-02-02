#pragma once

#include "../Mesh.h"
#include "Cube.h"
#include "../Loader.h"

namespace shapes {
	graphics::Mesh *Cube(graphics::Material *material) {
		std::vector<glm::vec3> tangents;
		std::vector<glm::vec3> bitangents;
		graphics::loader::Loader::calculateTangentSpace(shapes::raw::Cube::vertices, shapes::raw::Cube::uvs, tangents,
		                                                bitangents);
		return new graphics::Mesh(shapes::raw::Cube::vertices, shapes::raw::Cube::indices, shapes::raw::Cube::uvs,
		                          shapes::raw::Cube::normals, tangents, bitangents, material);
	}
}