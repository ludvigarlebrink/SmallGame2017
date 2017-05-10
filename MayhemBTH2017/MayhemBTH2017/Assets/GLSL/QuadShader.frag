#version 420

uniform sampler2D DiffuseMap;
in vec3 TexCoords1;
out vec4 FragColor;

uniform bool Shake;
uniform bool Chaos;
uniform float Time;


const float offset = 1.0 / 300;

const float blurr = 16;




void main()
{
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0.0f,	  offset),
		vec2(offset,  offset),
		vec2(-offset, 0.0f),
		vec2(0.0,     0.0f),
		vec2(offset,  0.0f),
		vec2(-offset, -offset),
		vec2(0.0f,    -offset),
		vec2(offset,  -offset));

	
	float kernalB[9] = float[](
	1.0/blurr, 2.0/blurr, 1.0/blurr,
	2.0/blurr, 4.0/blurr, 2.0/blurr,
	1.0/blurr, 2.0/blurr, 1.0/blurr);

	float kernalS[9] = float[](
	-1,-1,-1,
	-1, 9,-1,
	-1,-1,-1);

	vec3 sampleTex[9];
	for(int i =0; i<9;i++)
	{
		sampleTex[i] = vec3(texture(DiffuseMap,TexCoords1.xy +offsets[i]));
	}

	vec4 col;
	//col = texture2D(DiffuseMap, TexCoords1.xy);

	if(Shake)
	{
		for(int i =0;i<9;i++)
			col += vec4(sampleTex[i] * kernalB[i], 0.0f);
			col.a = 1.0f;
	}
	else if(Chaos)
	{
		col = 1 - texture2D(DiffuseMap, TexCoords1.xy);
	}
	else if(Chaos || Shake)
	{
		col = texture2D(DiffuseMap, TexCoords1.xy);
	}
	else
	{
		col = texture2D(DiffuseMap, TexCoords1.xy);
	}


	FragColor = col;

}