#version 400 core

struct DirectionalLight {
	vec3 direction;
	vec3 color;
};

in vec2 uv;
in vec3 norm;
in vec3 world;

out vec4 color;

uniform sampler2D texDiffuse;

uniform int amountDirLights;
uniform DirectionalLight dirLight;
uniform vec3 viewPos;

vec4 calcDirLight(DirectionalLight light, vec3 viewDir, vec3 normal) {
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	vec4 ambient = vec4(0.1);
	vec4 diffuse = vec4(diff * light.color, 1.0);
	vec4 specular = vec4(spec * light.color, 1.0);

	return (ambient + diffuse + specular);
}

void main() {
	vec3 normal = normalize(norm);
	vec3 viewDir = normalize(viewPos - world);

	vec4 result = calcDirLight(dirLight, viewDir, normal) * texture(texDiffuse, uv);

	color = result;
}