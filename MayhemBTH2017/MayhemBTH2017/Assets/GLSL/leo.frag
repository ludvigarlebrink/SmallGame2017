#version 420

out vec4 Colour;

uniform sampler2D texture;

in vec2 UV;

void main()
{
	vec4 col = vec4(texture2D(texture, UV).rgb, 1.0);
}