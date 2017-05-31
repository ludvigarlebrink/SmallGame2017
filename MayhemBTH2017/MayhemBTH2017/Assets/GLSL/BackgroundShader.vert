#version 420

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec3 TexCoords;

out vec3 TexCoords1;
out vec3 Normal1;
out vec3 FragPos;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


void main()
{

	gl_Position = vec4(Position.xy, 0.99f, 1.0f);
	
	FragPos = vec3(M * vec4(Position, 1.0));
	Normal1 = Normal;
	TexCoords1 = TexCoords;
}