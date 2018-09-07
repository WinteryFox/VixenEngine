#include "Loader.h"

namespace graphics::loader {
	graphics::model::Model Loader::loadModel(const std::string &path) {
		std::vector<graphics::model::Mesh*> meshes;
		
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
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
			Material *material = new Material();
			
			if (!mesh->HasTextureCoords(0))
				throw std::runtime_error("Mesh does not have texture coordinates, please export them and try again.");
			
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
			if (aiReturn_SUCCESS ==
					aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &mPath)) {
				std::string temp = path.substr(0, path.find_last_of('/')) + "/";
				temp += mPath.C_Str();
				
				aiColor4D aiAmbient;
				aiColor4D aiDiffuse;
				aiColor4D aiSpecular;
				float shininess;
				
				aiMat->Get(AI_MATKEY_COLOR_AMBIENT, aiAmbient);
				aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, aiDiffuse);
				aiMat->Get(AI_MATKEY_COLOR_SPECULAR, aiSpecular);
				aiMat->Get(AI_MATKEY_SHININESS, shininess);
				
				material = new Material(loadTexture(temp.c_str()), vec3(aiAmbient.r, aiAmbient.g, aiAmbient.b), vec3(aiDiffuse.r, aiDiffuse.g, aiDiffuse.b), vec3(aiSpecular.r, aiSpecular.g, aiSpecular.b), shininess);
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
			
			meshes.push_back(new graphics::model::Mesh(vertices, indices, uvs, normals, material));
		}
		
		return graphics::model::Model(meshes);
	}
	
	GLuint Loader::loadTexture(const char *file_name) {
		png_byte header[8];
		
		FILE *fp = fopen(file_name, "rb");
		if (fp == 0)
		{
			perror(file_name);
			return 0;
		}
		
		// read the header
		fread(header, 1, 8, fp);
		
		if (png_sig_cmp(header, 0, 8))
		{
			fprintf(stderr, "error: %s is not a PNG.\n", file_name);
			fclose(fp);
			return 0;
		}
		
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
		{
			fprintf(stderr, "error: png_create_read_struct returned 0.\n");
			fclose(fp);
			return 0;
		}
		
		// create png info struct
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			fprintf(stderr, "error: png_create_info_struct returned 0.\n");
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			fclose(fp);
			return 0;
		}
		
		// create png info struct
		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info)
		{
			fprintf(stderr, "error: png_create_info_struct returned 0.\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
			fclose(fp);
			return 0;
		}
		
		// the code in this if statement gets called if libpng encounters an error
		if (setjmp(png_jmpbuf(png_ptr))) {
			fprintf(stderr, "error from libpng\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			return 0;
		}
		
		// init png reading
		png_init_io(png_ptr, fp);
		
		// let libpng know you already read the first 8 bytes
		png_set_sig_bytes(png_ptr, 8);
		
		// read all the info up to the image data
		png_read_info(png_ptr, info_ptr);
		
		// variables to pass to get info
		int bit_depth, color_type;
		png_uint_32 temp_width, temp_height;
		
		// get info about png
		png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
		             NULL, NULL, NULL);
		
		//printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);
		
		if (bit_depth != 8)
		{
			fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", file_name, bit_depth);
			return 0;
		}
		
		GLint format;
		switch(color_type)
		{
			case PNG_COLOR_TYPE_RGB:
				format = GL_RGB;
				break;
			case PNG_COLOR_TYPE_RGB_ALPHA:
				format = GL_RGBA;
				break;
			default:
				fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name, color_type);
				return 0;
		}
		
		// Update the png info struct.
		png_read_update_info(png_ptr, info_ptr);
		
		// Row size in bytes.
		int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
		
		// glTexImage2d requires rows to be 4-byte aligned
		rowbytes += 3 - ((rowbytes-1) % 4);
		
		// Allocate the image_data as a big block, to be given to opengl
		png_byte * image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
		if (image_data == NULL)
		{
			fprintf(stderr, "error: could not allocate memory for PNG image data\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			return 0;
		}
		
		// row_pointers is for pointing to image_data for reading the png with libpng
		png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
		if (row_pointers == NULL)
		{
			fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			free(image_data);
			fclose(fp);
			return 0;
		}
		
		// set the individual row_pointers to point at the correct offsets of image_data
		for (unsigned int i = 0; i < temp_height; i++)
		{
			row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
		}
		
		// read the png into image_data through row_pointers
		png_read_image(png_ptr, row_pointers);
		
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		// clean up
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(image_data);
		free(row_pointers);
		fclose(fp);
		
		return texture;
	}
}