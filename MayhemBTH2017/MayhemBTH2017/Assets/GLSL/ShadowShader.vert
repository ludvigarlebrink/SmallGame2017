#version 420

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 TexCoords;

out vec3 TexCoords1;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 LightSpaceMatrix;

void main()
{

	if(TexCoords.z > 0.01f)
	{
		gl_Position = LightSpaceMatrix * vec4(Position, 1.0);

	}
	else
	{
		gl_Position = LightSpaceMatrix * M * vec4(0, 0, -1000, 1.0f);
	}
	TexCoords1 = TexCoords;
}
