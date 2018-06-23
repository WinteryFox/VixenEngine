#include "Loader.h"

namespace graphics::loader {
	graphics::model::Mesh Loader::loadMesh(const char *path) {
		std::vector<vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<vec2> uvs;
		std::vector<vec3> normals;
		
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, 0);
		if (!scene) {
			throw std::runtime_error(std::string("Assimp: ") + importer.GetErrorString());
		}
		const aiMesh *mesh = scene->mMeshes[0];
		
		vertices.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D pos = mesh->mVertices[i];
			vertices.emplace_back(pos.x, pos.y, pos.z);
		}
		
		/*uvs.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D UVW = mesh->mTextureCoords[0][i];
			uvs.emplace_back(UVW.x, UVW.y);
		}*/
		
		normals.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D n = mesh->mNormals[i];
			normals.emplace_back(n.x, n.y, n.z);
		}
		
		indices.reserve(3 * mesh->mNumFaces);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			indices.push_back(mesh->mFaces[i].mIndices[0]);
			indices.push_back(mesh->mFaces[i].mIndices[1]);
			indices.push_back(mesh->mFaces[i].mIndices[2]);
		}
		
		return graphics::model::Mesh(vertices, indices, uvs, normals);
	}
}