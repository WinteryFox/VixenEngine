#include "Loader.h"

graphics::model::Mesh* graphics::loader::Loader::loadMesh(const char *path) {
	std::vector<vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	
	IrrXMLReader* xml = createIrrXMLReader("config.xml");
	
	
	
	delete xml;
	return new graphics::model::Mesh(vertices, indices, uvs, normals);
}
