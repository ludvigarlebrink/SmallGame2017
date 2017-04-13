#version 420


in vec2 Position;
in vec2 TexCoords;

out vec2 UV;

void main()
{
	gl_Position = vec4(Position, 0.0, 1.0);
	UV = TexCoords;
}