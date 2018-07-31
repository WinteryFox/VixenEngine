#include "Loader.h"

namespace graphics::loader {
	graphics::model::Mesh Loader::loadMesh(const char *path) {
		std::vector<vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<vec2> uvs;
		std::vector<vec3> normals;
		GLuint texture;
		
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, 0);
		if (!scene) {
			throw std::runtime_error(std::string("Assimp: ") + importer.GetErrorString());
		}
		const aiMesh *mesh = scene->mMeshes[0];
		
		vertices.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D pos = mesh->mVertices[i];
			vertices.push_back(vec3(pos.x, pos.y, pos.z));
		}
		
		if (mesh->HasTextureCoords(0)) {
			uvs.reserve(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D UVW = mesh->mTextureCoords[0][i];
				uvs.push_back(vec2(UVW.x, UVW.y));
			}
			
			aiString peth;
			if (aiReturn_SUCCESS == scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &peth)) {
				char temp[256] = "../src/resources/";
				strcat(temp, static_cast<char*>(peth.data));
				texture = loadTexture(static_cast<const char*>(temp));
			}
		}
		
		normals.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D n = mesh->mNormals[i];
			normals.push_back(vec3(n.x, n.y, n.z));
		}
		
		indices.reserve(3 * mesh->mNumFaces);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			indices.push_back(mesh->mFaces[i].mIndices[0]);
			indices.push_back(mesh->mFaces[i].mIndices[1]);
			indices.push_back(mesh->mFaces[i].mIndices[2]);
		}
		
		return graphics::model::Mesh(vertices, indices, uvs, normals, texture);
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
		
		// Generate the OpenGL texture object
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