#version 420

out vec4 FragColor;


in vec3 position2;
in vec3 direction2;
in vec4 color2;
in float life2;
in float size2;

uniform sampler2D DiffuseMap;
in vec2 UV;


void main()
{

	
	vec4 tex=texture(DiffuseMap, UV);
	tex.a*=color2.a;
	FragColor = tex;
	
	

}