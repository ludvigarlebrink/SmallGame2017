#version 420

in vec2 TexCoords1;

out vec4 FragColor;


uniform sampler2D AlbedoMap;

void main()
{	
	vec4 rgba = texture2D(AlbedoMap, TexCoords1.xy).rgba;

	FragColor = rgba;
}