#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 norm;

out vec2 uv;
out vec3 normal;
out vec3 world;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(position, 1.0);
	world = vec3(model * vec4(position, 1.0));
	normal = mat3(transpose(inverse(model))) * norm;
	uv = texCoord;
}