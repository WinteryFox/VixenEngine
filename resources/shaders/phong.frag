#version 400 core

struct DirectionalLight {
	vec3 direction;
	vec3 color;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec2 uv;
in vec3 normal;
in vec3 world;

out vec4 color;

uniform sampler2D texDiffuse;

uniform Material material;

uniform int amountDirLights;
uniform DirectionalLight dirLight;
uniform vec3 viewPos;

vec4 calcDirLight(DirectionalLight light, vec3 viewDir, vec3 normal) {
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	vec4 ambient = vec4(light.color * material.ambient, 1.0);
	vec4 diffuse = vec4(light.color, 1.0) * vec4(diff * material.diffuse, 1.0);
	vec4 specular = vec4(light.color, 1.0) * vec4(spec * material.specular, 1.0);

	return (ambient + diffuse + specular);
}

void main() {
	vec3 viewDir = normalize(viewPos - world);

	vec4 result = calcDirLight(dirLight, viewDir, normal);
	color = result * texture(texDiffuse, uv);
}