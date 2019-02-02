#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 norm;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec2 uv;
out vec3 world;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(position, 1.0);
	world = vec3(model * vec4(position, 1.0));
	uv = texCoord;

	vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
	vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(norm, 0.0)));
	TBN = mat3(T, B, N);
}