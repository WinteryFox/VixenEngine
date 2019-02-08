#version 330 core

struct Light {
	int type;

	vec3 directional;

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
in vec3 world;
in mat3 TBN;
in vec3 normal;

out vec4 color;

uniform sampler2D texDiffuse;

uniform int hasNormal;
uniform sampler2D texNormal;

uniform vec3 viewPos;

uniform Material material;

uniform int lightCount;
uniform Light lights[16];

vec3 calcDirLight(Light light, vec3 viewDir, vec3 norm) {
	vec3 lightDir = normalize(-light.directional);
	float diff = max(dot(norm, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	vec3 ambient = material.ambient;
	vec3 diffuse = light.color * diff * material.diffuse;
	vec3 specular = light.color * spec * material.specular;

	return ambient + diffuse + specular;
}

vec3 calcPointLight(Light light, vec3 viewDir, vec3 norm) {
	vec3 lightDir = normalize(light.position - world);
	float diff = max(dot(norm, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - world);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = material.ambient * attenuation;
	vec3 diffuse = light.color * diff * material.diffuse * attenuation;
	vec3 specular = light.color * spec * material.specular * attenuation;

   return ambient + diffuse + specular;
}

void main() {
	vec3 viewDir = normalize(viewPos - world);
	vec4 result = vec4(0.0);

	vec4 tex = texture(texDiffuse, uv);
	if (tex.a < 0.5) {
		discard;
	}

	vec3 norm = normalize(normal);
	if (hasNormal == 1) {
		norm = texture(texNormal, uv).rgb;
		norm = normalize(norm * 2.0 - 1.0);
        norm = normalize(TBN * norm);
	}

	for (int i = 0; i < lightCount; i++) {
		if (lights[i].type == 0) {
			result += vec4(calcDirLight(lights[i], viewDir, norm), 1.0);
		} else {
			result += vec4(calcPointLight(lights[i], viewDir, norm), 1.0);
		}
	}

	color = result * tex;
	color = clamp(color, 0.0, 1.0);
}