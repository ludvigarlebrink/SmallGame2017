#version 420

in vec3 Normal1;

out vec4 FragColor;

void main()
{
	vec3 lightColor = vec3(1.0, 1.0, 0.0);
	vec3 col1 = vec3(0.0, 0.3, 0.0);
	vec3 col2 = vec3(0.0, 0.5, 0.0);
	vec3 col3 = vec3(0.0, 0.7, 0.0);

	vec3 lightDir = vec3(0, 3.0f, 7.0f);
	lightDir = normalize(lightDir);

	vec3 ambient = vec3(0.2f);
	
	float intensity = dot(Normal1, lightDir);
	vec3 rgb = vec3(0.6f, 1.0, 0);

	
    if(intensity<0.13)
        lightColor.xyz=vec3(0.05, 0.05, 0.05);

    if(intensity>=0.13 && intensity<0.33)
        lightColor.xyz=col1;

    if(intensity>=0.33 && intensity<0.66)
        lightColor.xyz=col2;

    if(intensity>=0.66 && intensity<0.88)
        lightColor.xyz=col3;

    if(intensity>=0.88)
        lightColor.xyz=vec3(0.9, 0.9, 0.9);
	
	
	FragColor = vec4((rgb * lightColor) + ambient, 1);

}