#include <utility>
#include <fstream>

#include "Loader.h"

namespace graphics::loader {
	graphics::model::Model* Loader::loadModel(std::string file) {
		try {
			std::vector<graphics::Mesh*> meshes;
			
			std::string path = resourcePath + file;
			
			Assimp::Importer importer;
			const aiScene *scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_PreTransformVertices);
			if (!scene) {
				throw std::runtime_error(std::string("Assimp: ") + importer.GetErrorString());
			}
			
			glm::mat4 rootNodeMatrix = glm::rotate(glm::mat4(1.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			
			for (unsigned int j = 0; j < scene->mNumMeshes; j++) {
				aiMesh *mesh = scene->mMeshes[j];
				
				std::vector<vec3> vertices;
				std::vector<unsigned int> indices;
				std::vector<vec2> uvs;
				std::vector<vec3> normals;
				graphics::Material material = Material(new Texture(0), vec3(0.0f), vec3(0.0f), vec3(0.0f), 0.0f);
				
				if (!mesh->HasTextureCoords(0))
					throw std::runtime_error(
							"Mesh does not have UV coordinates, please export them and try again.");
				
				for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
					aiVector3D pos = mesh->mVertices[i];
					vertices.emplace_back(pos.x, pos.y, pos.z);
				}
				
				for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
					aiVector3D UVW = mesh->mTextureCoords[0][i];
					uvs.emplace_back(UVW.x, UVW.y);
				}
				
				aiMaterial *aiMat = scene->mMaterials[mesh->mMaterialIndex];
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
					
					material = Material(generateTexture(loadImage(temp), GL_NEAREST),
					                    vec3(aiAmbient.r, aiAmbient.g, aiAmbient.b),
					                    vec3(aiDiffuse.r, aiDiffuse.g, aiDiffuse.b),
					                    vec3(aiSpecular.r, aiSpecular.g, aiSpecular.b), shininess);
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
				
				meshes.push_back(new graphics::Mesh(vertices, indices, uvs, normals, material));
			}
			return new graphics::model::Model(meshes);
		} catch (std::runtime_error &exception) {
			std::cout << "Failed to load model: " << exception.what() << std::endl;
			exit(1);
			// TODO: Load fallback model
		}
	}
	
	graphics::Image* Loader::loadImage(std::string file, bool flipped) {
		std::string path = resourcePath + file;
		
		std::ifstream stream(path.c_str(), std::ios::binary);
		if (!stream.is_open()) {
			std::cerr << "Failed to open image file " << file << ". Are you sure you're in the right directory?" << std::endl;
			return nullptr;
		}
		
		unsigned int SIGSIZE = 8;
		
		png_byte header[SIGSIZE];
		stream.read((char*) header, SIGSIZE);
		
		if (!stream.good()) {
			std::cerr << "Failed to read from file " << file << ". Maybe a permissions error?" << std::endl;
			return nullptr;
		}
		
		if (png_sig_cmp(header, 0, SIGSIZE) != 0) {
			std::cerr << "Invalid signature in file " << file << ". Is it a PNG?" << std::endl;
			return nullptr;
		}
		
		png_structp readPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		if (!readPointer) {
			std::cerr << "Failed to initialize png read struct from " << path << "." << std::endl;
			return nullptr;
		}
		
		png_infop infoPointer = png_create_info_struct(readPointer);
		if (!infoPointer) {
			std::cerr << "Failed to initialize png info struct from " << path << "." << std::endl;
			png_destroy_read_struct(&readPointer, nullptr, nullptr);
			return nullptr;
		}
		
		png_bytep* rowPointers = nullptr;
		char* data = nullptr;
		
		if (setjmp(png_jmpbuf(readPointer))) {
			png_destroy_read_struct(&readPointer, &infoPointer, nullptr);
			if (rowPointers)
				delete[] rowPointers;
			if (data)
				delete[] data;
			
			std::cerr << "Something borked while reading file " << path << std::endl;
			return nullptr;
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
		
		return new Image(GL_RGBA, width, height, data);
	}
	
	void Loader::readData(png_structp readPointer, png_bytep data, png_size_t length) {
		((std::ifstream*) png_get_io_ptr(readPointer))->read((char*) data, length);
	}
	
	graphics::Texture* Loader::generateTexture(Image* image, GLint filter) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, image->format, image->width, image->height, 0, image->format, GL_UNSIGNED_BYTE, image->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		return new graphics::Texture(texture);
	}
}