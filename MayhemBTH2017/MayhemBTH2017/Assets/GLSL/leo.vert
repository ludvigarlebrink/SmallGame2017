#version 420


in vec2 Position;

void main()
{
	gl_Position = vec4(Position, 0.0, 1.0);
}