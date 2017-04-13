#version 420

out vec4 Colour;

uniform sampler2D texture;

in vec2 UV;

void main()
{
	vec4 col = vec4(texture(texture, UV).rgb, 1.0);

	Colour = vec4(0.0, 1.0, 0.0, 1.0);
}