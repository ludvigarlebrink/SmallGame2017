#version 420

in vec3 TexCoords1;

out vec4 FragColor;



uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


uniform vec4 selectedUV;

uniform float Alpha;
uniform sampler2D DiffuseMap;
uniform sampler2D t;

void main()
{

	vec2 spriteUV = selectedUV.xy + (TexCoords1 * selectedUV.zw);


	FragColor = texture2D(t, vec2(spriteUV.x,  -spriteUV.y));
	//FragColor = texture2D(t, vec2(TexCoords1.x, -TexCoords1.y));
}