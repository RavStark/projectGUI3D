#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

uniform float offsetX = 0.0f;
uniform float offsetY = 0.0f;

uniform vec3 lightPos;
uniform mat4 model;
uniform mat4 inverseModelView;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	TexCoord = texCoord;
	FragPos = vec3(view * model * vec4(position, 1.0f));
	Normal = mat3(transpose(inverseModelView)) * normal;  
	LightPos = vec3(view * vec4(lightPos, 1.0f));
}