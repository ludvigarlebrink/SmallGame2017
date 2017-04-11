#version 420


in vec3 Position;


void main()
{
	gl_Position = vec4(Position, 0.5, 1.0);

}