#version 420

in vec3 Normal1;

out vec4 FragColor;
uniform sampler2D DiffuseMap;
in vec3 UV;

void main()
{
	
	vec4 tex=texture(DiffuseMap, UV.xy);
	vec3 lightDir = vec3(0, 3.0f, 7.0f);
	lightDir = normalize(lightDir);

	vec3 ambient = vec3(0.2f);
	
	float i = abs(dot(Normal1, lightDir));
	vec3 rgb = vec3(0.0f, 1.0, 1.0f);
	FragColor = vec4((rgb * i) + ambient, 0.5);
	

}