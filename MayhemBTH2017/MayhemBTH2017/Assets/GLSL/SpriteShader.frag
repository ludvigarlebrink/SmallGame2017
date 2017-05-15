#version 420

in vec2 TexCoords1;

out vec4 FragColor;

uniform int Greyscale;
uniform sampler2D AlbedoMap;

void main()
{	
	vec4 rgba = texture2D(AlbedoMap, TexCoords1.xy).rgba;

	if(Greyscale > 0.01)
	{
		float color =  0.299 * rgba.r + 0.587 * rgba.g + 0.114 * rgba.b;
		color *= 0.5;
		FragColor = vec4(color, color * 1.3f, color, rgba.a);
	}
	else
	{
		FragColor = rgba;
	}
}