#version 420

out vec4 FragColor;
in vec3 finalCol;
in vec2 UV;
uniform sampler2D DiffuseMap;
in vec4 color2;


void main()
{

	
	vec4 tex=texture(DiffuseMap, UV);
	FragColor = tex;
	
	

}