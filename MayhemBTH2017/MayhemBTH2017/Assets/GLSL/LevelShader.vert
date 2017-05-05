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
uniform float Alpha;

void main()
{

	if(TexCoords.z > 0.01f)
	{
		mat4 PV = P * V;
		mat4 MVP = PV * M;
		gl_Position = MVP * vec4(Position, 1.0f);
	}
	FragPos = vec3(M * vec4(Position, 1.0));
	Normal1 = Normal;
	TexCoords1 = TexCoords;
}

