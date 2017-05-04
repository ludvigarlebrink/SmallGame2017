#version 420



out vec4 FragColor;
uniform sampler2D DiffuseMap;

in vec2 UV1;

void main()
{
	

	vec4 tex=texture(DiffuseMap, UV1.xy);
	FragColor = tex;
}