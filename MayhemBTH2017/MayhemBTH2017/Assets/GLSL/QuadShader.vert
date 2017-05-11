#version 420

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 TexCoords;

out vec3 TexCoords1;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform bool Shake;
uniform bool Chaos;
uniform float STime;
uniform float CTime;


void main()
{
	gl_Position =  vec4(Position, 1.0f);
	TexCoords1 = TexCoords;
	if(Shake)
	{
		float strenght = 0.01;
		gl_Position.x += cos(STime * 10) * strenght;
		gl_Position.y += cos(STime * 15) * strenght;
			
	}
	if(Chaos)
	{
		TexCoords1 = vec3(1.0- TexCoords.x, 1.0 - TexCoords.y, 1.0);
	}

	
}

