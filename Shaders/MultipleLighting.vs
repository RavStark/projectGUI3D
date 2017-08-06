#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

uniform float offsetX = 0.0f;
uniform float offsetY = 0.0f;

uniform mat4 model;
uniform mat4 inverseModelView;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

void main()
{
	FragPos = vec3(model * vec4(position, 1.0f));
	
	TexCoords = texCoord;
	
	Normal = mat3(transpose(inverseModelView)) * normal;  
	gl_Position = projection * view * model * vec4(position, 1.0f);
}