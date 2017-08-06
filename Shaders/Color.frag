#version 330 core

uniform vec3 our_color;

out vec4 color;

void main()
{
	color = vec4(our_color.x,our_color.y,our_color.z,0.0f);
}