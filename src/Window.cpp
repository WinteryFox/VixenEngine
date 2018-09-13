#include <iostream>
#include "Window.h"

namespace graphics {
	Window::Window(const char *name, int width, int height) : name(name), width(width), height(height) {
		if (!init())
			glfwTerminate();
	}
	
	Window::~Window() {
		glfwSetWindowShouldClose(window, GL_TRUE);
		glfwTerminate();
	}
	
	bool Window::init() {
		if (!glfwInit()) {
			std::cout << "Failed to initialise GLFW" << std::endl;
			return false;
		}
		
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
		
		window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		if (!window) {
			std::cout << "Failed to create window" << std::endl;
			return false;
		}
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialise GLEW" << std::endl;
			return false;
		}
		
		glfwSwapInterval(0);
		
		setIcon("../resources/textures/icon.png");
		
		return true;
	}
	
	void Window::update() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		
		auto current = static_cast<float>(glfwGetTime());
		deltaTime = current - lastTime;
		FPSTime = current - lastFPS;
		lastTime = current;
		fps++;
		if (FPSTime >= 1.0) {
			std::cout << fps << " fps" << std::endl;
			fps = 0;
			lastFPS = current;
		}
	}
	
	void Window::swap() {
		glfwSwapBuffers(window);
	}
	
	bool Window::shouldClose() const {
		return glfwWindowShouldClose(window) == 1;
	}
	
	GLFWwindow *Window::getWindow() {
		return window;
	}
	
	float Window::getDeltaTime() {
		return deltaTime;
	}
	
	void Window::setIcon(const char *file_name) {
		png_byte header[8];
		
		FILE *fp = fopen(file_name, "rb");
		if (fp == 0) {
			perror(file_name);
			throw std::runtime_error("Failed to open file");
		}
		
		// read the header
		fread(header, 1, 8, fp);
		
		if (png_sig_cmp(header, 0, 8)) {
			fprintf(stderr, "error: %s is not a PNG.\n", file_name);
			fclose(fp);
			throw std::runtime_error("Failed to open file 0");
		}
		
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr) {
			fprintf(stderr, "error: png_create_read_struct returned 0.\n");
			fclose(fp);
			throw std::runtime_error("Failed to open file 1");
		}
		
		// create png info struct
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			fprintf(stderr, "error: png_create_info_struct returned 0.\n");
			png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
			fclose(fp);
			throw std::runtime_error("Failed to open file 2");
		}
		
		// create png info struct
		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info) {
			fprintf(stderr, "error: png_create_info_struct returned 0.\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
			fclose(fp);
			throw std::runtime_error("Failed to open file 3");
		}
		
		// the code in this if statement gets called if libpng encounters an error
		if (setjmp(png_jmpbuf(png_ptr))) {
			fprintf(stderr, "error from libpng\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			throw std::runtime_error("Failed to open file 4");
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
		
		if (bit_depth != 8) {
			fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", file_name, bit_depth);
			throw std::runtime_error("Failed to open file 5");
		}
		
		GLint format;
		switch (color_type) {
			case PNG_COLOR_TYPE_RGB:
				format = GL_RGB;
				break;
			case PNG_COLOR_TYPE_RGB_ALPHA:
				format = GL_RGBA;
				break;
			default:
				fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name, color_type);
				throw std::runtime_error("Failed to open file 6");
		}
		
		// Update the png info struct.
		png_read_update_info(png_ptr, info_ptr);
		
		// Row size in bytes.
		int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
		
		// glTexImage2d requires rows to be 4-byte aligned
		rowbytes += 3 - ((rowbytes - 1) % 4);
		
		// Allocate the image_data as a big block, to be given to opengl
		png_byte *image_data = (png_byte *) malloc(rowbytes * temp_height * sizeof(png_byte) + 15);
		if (image_data == NULL) {
			fprintf(stderr, "error: could not allocate memory for PNG image data\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			throw std::runtime_error("Failed to open file 7");
		}
		
		// row_pointers is for pointing to image_data for reading the png with libpng
		png_byte **row_pointers = (png_byte **) malloc(temp_height * sizeof(png_byte * ));
		if (row_pointers == NULL) {
			fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			free(image_data);
			fclose(fp);
			throw std::runtime_error("Failed to open file 8");
		}
		
		// set the individual row_pointers to point at the correct offsets of image_data
		for (unsigned int i = 0; i < temp_height; i++)
		{
			png_uint_32 q = (temp_height - i - 1) * rowbytes;
			row_pointers[temp_height - i - 1] = (png_bytep) image_data + q;
		}
		
		// read the png into image_data through row_pointers
		png_read_image(png_ptr, row_pointers);
		
		GLFWimage image;
		image.width = temp_width;
		image.height = temp_height;
		image.pixels = image_data;
		
		glfwSetWindowIcon(window, 1, &image);
		
		// clean up
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(image_data);
		free(row_pointers);
		fclose(fp);
	}
}
