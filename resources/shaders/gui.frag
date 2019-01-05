#version 330 core

in vec2 uv;

out vec4 outColor;

uniform vec3 color;
uniform sampler2D font;

void main() {
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(font, uv).r);
	outColor = vec4(color, 1.0) * sampled;
}