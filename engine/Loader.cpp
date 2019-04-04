#include <utility>
#include <fstream>

#include "Loader.h"

namespace graphics::loader {
	graphics::model::Model *Loader::loadModel(std::string file) {
		std::vector<graphics::Mesh *> meshes;
		
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(file, aiProcessPreset_TargetRealtime_MaxQuality |
		                                               aiProcess_PreTransformVertices | aiProcess_CalcTangentSpace |
		                                               aiProcess_Triangulate);
		if (!scene) {
			//if (file == resourcePath + "models/missing.dae")
			//	exit(0x5);
			// TODO
			std::cerr << "Failed to open file " << file << std::endl;
			std::cerr << importer.GetErrorString() << std::endl;
			//return loadModel(resourcePath + "models/missing.dae");
			return nullptr;
		}
		
		for (unsigned int j = 0; j < scene->mNumMeshes; j++) {
			aiMesh *mesh = scene->mMeshes[j];
			
			std::vector<vec3> vertices;
			std::vector<unsigned int> indices;
			std::vector<vec2> uvs;
			std::vector<vec3> normals;
			std::vector<vec3> tangents;
			std::vector<vec3> bitangents;
			graphics::Material *material;
			
			if (!mesh->HasTextureCoords(0)) {
				std::cerr << "Mesh is missing texture coordinates, loaded fallback model" << std::endl;
				return loadModel("models/missing.dae");
			}
			
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D pos = mesh->mVertices[i];
				vertices.emplace_back(pos.x, pos.y, pos.z);
			}
			
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D UVW = mesh->mTextureCoords[0][i];
				uvs.emplace_back(UVW.x, UVW.y);
			}
			
			aiMaterial *aiMat = scene->mMaterials[mesh->mMaterialIndex];
			
			if (aiMat == nullptr) {
				std::cerr << "Mesh is malformed (missing material), using fallback material." << std::endl;
				material = new Material(vec3(0.1f),
				                        vec3(1.0f),
				                        vec3(0.0f), 0.0f,
				                        generateTexture(loadImage("models/missing.png")));
			} else {
				aiString mPath;
				if (aiReturn_SUCCESS == aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &mPath)) {
					std::string temp = file.substr(0, file.find_last_of('/')) + "/";
					temp += mPath.C_Str();
					
					aiColor4D aiAmbient;
					aiColor4D aiDiffuse;
					aiColor4D aiSpecular;
					float shininess;
					
					aiMat->Get(AI_MATKEY_COLOR_AMBIENT, aiAmbient);
					aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, aiDiffuse);
					aiMat->Get(AI_MATKEY_COLOR_SPECULAR, aiSpecular);
					aiMat->Get(AI_MATKEY_SHININESS, shininess);
					
					material = new Material(vec3(aiAmbient.r, aiAmbient.g, aiAmbient.b),
					                        vec3(aiDiffuse.r, aiDiffuse.g, aiDiffuse.b),
					                        vec3(aiSpecular.r, aiSpecular.g, aiSpecular.b), shininess,
					                        generateTexture(loadImage(temp)));
				} else {
					std::cerr << "Failed to find diffuse texture for model " << file << std::endl;
					material = new Material(vec3(0.1f),
					                        vec3(1.0f),
					                        vec3(0.0f), 0.0f,
					                        generateTexture(loadImage("models/missing.png")));
				}
				
				if (aiReturn_SUCCESS == aiMat->GetTexture(aiTextureType_NORMALS, 0, &mPath)) {
					std::string temp = file.substr(0, file.find_last_of('/')) + "/";
					temp += mPath.C_Str();
					std::cout << temp << std::endl;
					
					material->tNormal = generateTexture(loadImage(temp));
				} else {
					material->tNormal = new Texture(0);
					std::cout << "Mesh does not have a normal map" << std::endl;
				}
			}
			
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D n = mesh->mNormals[i];
				normals.emplace_back(n.x, n.y, n.z);
			}
			
			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
				indices.push_back(mesh->mFaces[i].mIndices[0]);
				indices.push_back(mesh->mFaces[i].mIndices[1]);
				indices.push_back(mesh->mFaces[i].mIndices[2]);
			}
			
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				tangents.emplace_back(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
			}
			
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				bitangents.emplace_back(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
			}
			
			meshes.push_back(new graphics::Mesh(vertices, indices, uvs, normals, tangents, bitangents, material));
		}
		return new graphics::model::Model(meshes);
	}
	
	void Loader::calculateTangentSpace(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uvs,
	                                   const std::vector<unsigned int> &indices,
	                                   std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &bitangents) {
		tangents.reserve(vertices.size() / 3);
		bitangents.reserve(vertices.size() / 3);
		for (unsigned int i = 0; i < indices.size() / 3; i++) {
			glm::vec3 pos1 = vertices[indices[i * 3]];
			glm::vec3 pos2 = vertices[indices[i * 3 + 1]];
			glm::vec3 pos3 = vertices[indices[i * 3 + 2]];
			
			glm::vec2 uv1 = uvs[indices[i * 3]];
			glm::vec2 uv2 = uvs[indices[i * 3 + 1]];
			glm::vec2 uv3 = uvs[indices[i * 3 + 2]];
			
			glm::vec3 edge1 = pos2 - pos1;
			glm::vec3 edge2 = pos3 - pos1;
			glm::vec2 deltaUV1 = uv2 - uv1;
			glm::vec2 deltaUV2 = uv3 - uv1;
			
			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
			
			glm::vec3 tangent = glm::vec3(f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
			                  f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
			                  f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z));
			glm::normalize(tangent);
			tangents.push_back(tangent);
			
			glm::vec3 bitangent = glm::vec3(f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x),
			                    f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y),
			                    f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z));
			glm::normalize(bitangent);
			bitangents.push_back(bitangent);
		}
	}
	
	graphics::Image *Loader::loadImage(std::string file, bool flipped) {
		
		std::ifstream stream(file.c_str(), std::ios::binary);
		if (!stream.is_open()) {
			if (file == "textures/missing.png" || file == "models/missing.png")
				exit(0x5);
			std::cerr << "Failed to open image file " << file << ". Are you sure you're in the right directory?"
			          << std::endl;
			return loadImage("models/missing.png");
		}
		
		unsigned int SIGSIZE = 8;
		
		png_byte header[SIGSIZE];
		stream.read((char *) header, SIGSIZE);
		
		if (!stream.good()) {
			std::cerr << "Failed to read from file " << file << ". Maybe a permissions error?" << std::endl;
			return loadImage("models/missing.png");
		}
		
		if (png_sig_cmp(header, 0, SIGSIZE) != 0) {
			std::cerr << "Invalid signature in file " << file << ". Is it a PNG?" << std::endl;
			return loadImage("models/missing.png");
		}
		
		png_structp readPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		if (!readPointer) {
			std::cerr << "Failed to initialize png read struct from " << file << "." << std::endl;
			return loadImage("models/missing.png");
		}
		
		png_infop infoPointer = png_create_info_struct(readPointer);
		if (!infoPointer) {
			std::cerr << "Failed to initialize png info struct from " << file << "." << std::endl;
			png_destroy_read_struct(&readPointer, nullptr, nullptr);
			return loadImage("models/missing.png");
		}
		
		png_bytep *rowPointers = nullptr;
		char *data = nullptr;
		
		if (setjmp(png_jmpbuf(readPointer))) {
			png_destroy_read_struct(&readPointer, &infoPointer, nullptr);
			if (rowPointers)
				delete[] rowPointers;
			if (data)
				delete[] data;
			
			std::cerr << "Something borked while reading file " << file << std::endl;
			return loadImage("models/missing.png");
		}
		
		png_set_read_fn(readPointer, (png_voidp) &stream, readData);
		
		png_set_sig_bytes(readPointer, SIGSIZE);
		png_read_info(readPointer, infoPointer);
		
		png_uint_32 width = png_get_image_width(readPointer, infoPointer);
		png_uint_32 height = png_get_image_height(readPointer, infoPointer);
		png_uint_32 bitdepth = png_get_bit_depth(readPointer, infoPointer);
		png_uint_32 channels = png_get_channels(readPointer, infoPointer);
		png_uint_32 colorType = png_get_color_type(readPointer, infoPointer);
		
		if (png_get_valid(readPointer, infoPointer, PNG_INFO_tRNS)) {
			png_set_tRNS_to_alpha(readPointer);
			channels += 1;
		}
		
		if (bitdepth == 16)
			png_set_strip_16(readPointer);
		
		GLenum type;
		switch (colorType) {
			case PNG_COLOR_TYPE_RGB:
				type = GL_RGB;
				break;
			case PNG_COLOR_TYPE_RGBA:
				type = GL_RGBA;
				break;
		}
		
		png_read_update_info(readPointer, infoPointer);
		
		rowPointers = new png_bytep[height];
		data = new char[(width * height * bitdepth * channels) >> 3];
		const unsigned int stride = (width * bitdepth * channels) >> 3;
		
		if (!flipped) {
			for (size_t i = 0; i < height; i++) {
				rowPointers[i] = (png_bytep) data + (height - i - 1) * stride;
			}
		} else {
			for (size_t i = 0; i < height; i++) {
				rowPointers[height - i - 1] = (png_bytep) data + (height - i - 1) * stride;
			}
		}
		
		png_read_image(readPointer, rowPointers);
		
		delete[] (png_bytep) rowPointers;
		png_destroy_read_struct(&readPointer, &infoPointer, nullptr);
		stream.close();
		
		return new Image(type, width, height, data);
	}
	
	void Loader::readData(png_structp readPointer, png_bytep data, png_size_t length) {
		((std::ifstream *) png_get_io_ptr(readPointer))->read((char *) data, length);
	}
	
	graphics::Texture *Loader::generateTexture(Image *image) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, image->format, image->width, image->height, 0, image->format, GL_UNSIGNED_BYTE,
		             image->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		return new graphics::Texture(texture);
	}
	
	graphics::Texture *Loader::generateTexture(const std::string &texture) {
		return generateTexture(loadImage(texture));
	}
}