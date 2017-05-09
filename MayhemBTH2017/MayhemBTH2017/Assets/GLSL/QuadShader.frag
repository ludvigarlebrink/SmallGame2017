#version 420

uniform sampler2D DiffuseMap;
in vec3 TexCoords1;
out vec4 FragColor;

uniform bool Shake;
uniform bool Chaos;




void main()
{
	vec4 col;

	if(Shake)
	{
		col = (1,1,1,1);
	}
	else if(Chaos)
	{
		col = (0,0,0,0);
	}
	else
	{
		col = texture2D(DiffuseMap, TexCoords1.xy);
	}


	FragColor = col;

}