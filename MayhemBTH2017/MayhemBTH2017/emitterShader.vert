#version 420


layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoords;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


in vec3 inValue;
void main()
{
	mat4 PV = P * V;
	mat4 MVP = PV * M;
	gl_Position = MVP * vec4(inValue, 1.0);
}

