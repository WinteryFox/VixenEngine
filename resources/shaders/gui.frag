#version 330 core

in vec2 uv;

out vec4 outColor;

uniform vec3 color;
uniform sampler2D font;

void main() {
	outColor = vec4(color, texture(font, uv).a);
}