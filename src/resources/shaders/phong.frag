#version 330 core

struct DirectionalLight {
    vec3 position;
    vec3 color;
};

in vec2 uvs;

out vec4 color;

uniform sampler2D texture;
uniform DirectionalLight[1] dirLights;

void main() {
    color = texture2D(texture, uvs);
}