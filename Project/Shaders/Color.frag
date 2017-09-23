#version 330 core
out vec4 FragColor;
  
uniform vec3 ourColor;
uniform vec3 lightColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
void main()
{
    FragColor = vec4(lightColor * ourColor, 1.0f);//texture(ourTexture, TexCoord);
} 