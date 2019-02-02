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
	
	void Shader::loadMatrix4f(GLint location, const glm::mat4 &matrix) {
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}
	
	void Shader::loadVector2f(GLint location, const glm::vec2 &vector) {
		glUniform2fv(location, 1, &vector[0]);
	}
	
	void Shader::loadVector3f(GLint location, const glm::vec3 &vector) {
		glUniform3fv(location, 1, &vector[0]);
	}
	
	void Shader::loadInteger(GLint location, int integer) {
		glUniform1i(location, integer);
	}
	
	void Shader::loadMaterial(const shaders::Material &materialLocations, graphics::Material *material) {
		glUniform3fv(materialLocations.ambient, 1, &material->ambient[0]);
		glUniform3fv(materialLocations.diffuse, 1, &material->diffuse[0]);
		glUniform3fv(materialLocations.specular, 1, &material->specular[0]);
		glUniform1f(materialLocations.shininess, material->shininess);
		glUniform1i(materialLocations.hasNormal, material->tNormal->id == 0 ? 0 : 1);
	}
	
	void Shader::loadLight(const shaders::Light &lightLocations, const graphics::Light &light) {
		glUniform3f(lightLocations.color, static_cast<float>(light.color.x), static_cast<float>(light.color.y),
		            static_cast<float>(light.color.z));
		if (light.type == graphics::Light::DIRECTIONAL) {
			glUniform1i(lightLocations.type, 0);
			glUniform3fv(lightLocations.directional, 1, &light.direction[0]);
		} else {
			glUniform1i(lightLocations.type, 1);
			glUniform3fv(lightLocations.position, 1, &light.position[0]);
			glUniform1f(lightLocations.quadratic, light.quadratic);
			glUniform1f(lightLocations.linear, light.linear);
			glUniform1f(lightLocations.constant, light.constant);
		}
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
			std::cerr << "Impossible to open " << vertex.c_str() << ". Are you in the right directory?\n" << std::endl;
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
			std::string VertexShaderErrorMessage;
			glGetShaderInfoLog(vertexID, infoLogLength, nullptr, &VertexShaderErrorMessage[0]);
			std::cerr << VertexShaderErrorMessage << std::endl;
		}
		
		char const *FragmentSourcePointer = fragmentShaderCode.c_str();
		glShaderSource(fragmentID, 1, &FragmentSourcePointer, nullptr);
		glCompileShader(fragmentID);
		
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0) {
			std::string FragmentShaderErrorMessage;
			glGetShaderInfoLog(fragmentID, infoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
			std::cerr << FragmentShaderErrorMessage << std::endl;
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
			std::cerr << &ProgramErrorMessage[0] << std::endl;
		}
		
		glDetachShader(programID, vertexID);
		glDetachShader(programID, fragmentID);
		
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		
		return programID;
	}
}