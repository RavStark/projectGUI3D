#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	//ambient
	float ambientStrength  = 0.1f;
	vec3 ambient = ambientStrength  * lightColor;

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float angleToLight = max(dot(norm, lightDir), 0.0f);
	vec3 lightDiffuse = angleToLight * lightColor;

	//specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(-FragPos);// The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
	vec3 reflectDir = reflect(-lightDir, norm); //We inverse lightDir because the vector direction come from the light to the fragment
	float angleToView = pow(max(dot(reflectDir, viewDir), 0.0f), 124);
	vec3 specular = specularStrength * angleToView * lightColor;
	color = vec4((ambient + lightDiffuse + specular) * objectColor, 1.0f);
}