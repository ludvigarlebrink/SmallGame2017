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


	vec2 spriteUV = selectedUV.xy + (vec2(TexCoords1.x, TexCoords1.y)  * selectedUV.zw);


	//FragColor = vec4(0.0f, 1.0f, 0.0f, 0.5f);//texture2D(t, vec2(spriteUV.x,  -spriteUV.y));
	FragColor = texture2D(t, vec2(spriteUV.x,  spriteUV.y));
	//FragColor = texture2D(t, vec2(TexCoords1.x, -TexCoords1.y));
	//FragColor = vec4(0.0,0.0,1.0,0.0);


}