#version 420

in vec3 Normal1;
in vec3 TexCoords1;

uniform sampler2D AlbedoMap;

out vec4 FragColor;

void main()
{
	vec3 lightDir = vec3(0, 3.0f, 7.0f);
	lightDir = normalize(lightDir);

	vec3 ambient = vec3(0.2f);
	
	float i = abs(dot(Normal1, lightDir));
	vec3 rgb = vec3(0.6f, 0.0, 1.0);

	//FragColor = vec4((rgb * i) + ambient, 1);
	FragColor = texture2D(AlbedoMap, vec2(TexCoords1.x, -TexCoords1.y));

}