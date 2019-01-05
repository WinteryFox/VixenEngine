#version 330 core

layout(location = 1) in vec2 position;
layout(location = 2) in vec2 uvs;

out vec2 uv;

uniform vec2 translation;

void main() {
	gl_Position = vec4(position + translation * vec2(2.0, -2.0), 0.0, 1.0);
	uv = uvs;
}