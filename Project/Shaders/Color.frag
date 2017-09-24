#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 viewPosition;

//in vec2 TexCoord; //textCoord from vs
in vec3 Normal; //Normal vector from vs
in vec3 FragPos; //world position vertex
uniform sampler2D ourTexture;
void main()
{
	
    vec3 ambient = material.ambient * light.ambient;
    
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;
	
    // specular
    float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (material.specular * spec) * light.specular;  

	vec3 result = (ambient + diffuse + specular);
	FragColor = vec4(result, 1.0f);//texture(ourTexture, TexCoord);
} 