#pragma once

#include "../Mesh.h"
#include "Cube.h"

namespace shapes {
	graphics::Mesh *Cube() {
		return new graphics::Mesh(shapes::raw::Cube::vertices, shapes::raw::Cube::indices, shapes::raw::Cube::uvs,
		                          shapes::raw::Cube::normals,
		                          new graphics::Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.0f), 0.0f,
		                                                 graphics::loader::Loader::generateTexture(
				                                                 graphics::loader::Loader::loadImage(
						                                                 "models/missing.png"))));
	}
}