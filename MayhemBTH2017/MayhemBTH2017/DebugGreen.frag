#version 420

in vec3 TexCoords1;

out vec4 FragColor;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform sampler2D DiffuseMap;

void main()
{
	vec3 col = texture2D(DiffuseMap, TexCoords1.xy).xyz;
	
	FragColor = vec4(col.xyz, 1);
	

}