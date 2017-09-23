#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 color;

struct Light {
vec3 position;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Light light;
uniform Material material;
//uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float angleToLight = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = (angleToLight * material.diffuse) * light.diffuse;

	//specular
	vec3 viewDir = normalize(-FragPos);// The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
	vec3 reflectDir = reflect(-lightDir, norm); //We inverse lightDir because the vector direction come from the light to the fragment
	float angleToView = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specular = (material.specular * angleToView) * light.specular;
	color = vec4((ambient + diffuse + specular), 1.0f);
}