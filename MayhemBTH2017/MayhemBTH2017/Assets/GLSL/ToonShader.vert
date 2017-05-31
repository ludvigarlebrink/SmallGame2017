#version 420

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec3 TexCoordsAlpha;

out vec3 Normal1;
out vec3 TexCoords1;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	if(TexCoordsAlpha.z > 0.001f)
	{
		gl_Position = P * V * M * vec4(Position, 1.0f);
	}
	
	Normal1 = (M * vec4(Normal, 1.0)).xyz;
	TexCoords1 = TexCoordsAlpha;
}

