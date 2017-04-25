#version 420


in vec2 Position;


void main()
{

	float x=(Position.x-0.5);
	float y=(Position.y-0.5);
	gl_Position = vec4(x, y, 0.0, 1.0);
}