#include <utility>

#include <utility>

#include "Shader.h"

namespace shaders {
	Shader::Shader(std::string vertex, std::string fragment) {
		id = loadAndCompile(std::move(vertex), std::move(fragment));
	}
	
	Shader::~Shader() {
		stop();
		glDeleteProgram(id);
	}
	
	void Shader::start() {
		glUseProgram(id);
	}
	
	void Shader::stop() {
		glUseProgram(0);
	}
	
	// TODO: Move to a global loader
	GLuint Shader::loadAndCompile(std::string vertex, std::string fragment) {
		GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		
		vertex = resourcePath + "shaders/" + vertex;
		fragment = resourcePath + "shaders/" + fragment;
		
		std::string vertexShaderCode;
		std::ifstream vertexShaderStream(vertex, std::ios::in);
		if (vertexShaderStream.is_open()) {
			std::string line;
			while (getline(vertexShaderStream, line)) vertexShaderCode += "\n" + line;
			vertexShaderStream.close();
		} else {
			std::cout << "Impossible to open " << vertex.c_str() << ". Are you in the right directory?\n" << std::endl;
			getchar();
		}
		
		std::string fragmentShaderCode;
		std::ifstream fragmentShaderStream(fragment, std::ios::in);
		if (fragmentShaderStream.is_open()) {
			std::string line;
			while (getline(fragmentShaderStream, line)) fragmentShaderCode += "\n" + line;
			fragmentShaderStream.close();
		}
		
		GLint result = GL_FALSE;
		int infoLogLength;
		
		char const *VertexSourcePointer = vertexShaderCode.c_str();
		glShaderSource(vertexID, 1, &VertexSourcePointer, nullptr);
		glCompileShader(vertexID);
		
		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(vertexID, infoLogLength, nullptr, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}
		
		char const *FragmentSourcePointer = fragmentShaderCode.c_str();
		glShaderSource(fragmentID, 1, &FragmentSourcePointer, nullptr);
		glCompileShader(fragmentID);
		
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(fragmentID, infoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
			fprintf(stderr, "%s\n", &FragmentShaderErrorMessage[0]);
		}
		
		GLuint programID = glCreateProgram();
		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);
		glLinkProgram(programID);
		
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(infoLogLength + 1);
			glGetProgramInfoLog(programID, infoLogLength, nullptr, &ProgramErrorMessage[0]);
			std::cout << &ProgramErrorMessage[0] << std::endl;
		}
		
		glDetachShader(programID, vertexID);
		glDetachShader(programID, fragmentID);
		
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		
		return programID;
	}
}