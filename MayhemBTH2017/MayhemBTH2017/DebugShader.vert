#version 420

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 Mvp;

void main()
{
	gl_Position =  Mvp * vec4(position, 1.0);
}

