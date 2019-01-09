#version 400 core

struct DirectionalLight {
	vec3 direction;
	vec3 color;
};

struct PointLight {
	vec3 position;
	vec3 color;

	float quadratic;
	float linear;
	float constant;
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

uniform vec3 viewPos;

uniform Material material;

uniform int lightCount;
uniform DirectionalLight dirLight;
uniform PointLight lights[16];

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

vec4 calcPointLight(PointLight light, vec3 viewDir, vec3 normal) {
	vec3 lightDir = normalize(light.position);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - world);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec4 ambient = vec4(light.color * material.ambient, 1.0) * attenuation;
    vec4 diffuse = vec4(light.color, 1.0) * vec4(diff * material.diffuse, 1.0) * attenuation;
    vec4 specular = vec4(light.color, 1.0) * vec4(spec * material.specular, 1.0) * attenuation;

   return (ambient + diffuse + specular);
}

void main() {
	vec3 viewDir = normalize(viewPos - world);

	vec4 result = calcDirLight(dirLight, viewDir, normal);
	for (int i = 0; i < lightCount; i++)
		result += calcPointLight(lights[i], viewDir, normal);

	color = result * texture(texDiffuse, uv);
}