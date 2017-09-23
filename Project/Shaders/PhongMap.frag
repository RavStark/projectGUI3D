#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoord;

out vec4 color;

struct Light {
vec3 position;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

uniform Light light;
uniform Material material;
//uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float angleToLight = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * angleToLight * vec3(texture(material.diffuse, TexCoord));

	//specular
	vec3 viewDir = normalize(-FragPos);// The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
	vec3 reflectDir = reflect(-lightDir, norm); //We inverse lightDir because the vector direction come from the light to the fragment
	float angleToView = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specular = light.specular * angleToView * vec3(texture(material.specular, TexCoord));
	color = vec4((ambient + diffuse + specular), 1.0f);
	 //color = texture(ourTexture1, TexCoord);
}