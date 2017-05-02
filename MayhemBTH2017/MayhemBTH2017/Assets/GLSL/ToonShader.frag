#version 420

in vec3 Normal1;
in vec3 TexCoords1;

out vec4 FragColor;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform mat4 Joints[22];
uniform sampler2D AlbedoMap;

void main()
{
	vec3 lightColor = vec3(0.0f);
	vec3 col1 = vec3(0.4);
	vec3 col2 = vec3(0.6);
	vec3 col3 = vec3(0.9);

	vec3 lightDir = vec3(0.0f, 0.0f, 3.0f);
	lightDir = normalize(lightDir);

	vec3 ambient = vec3(0.2f);
	
	float intensity = clamp(dot(lightDir, Normal1), 0, 1);
	vec3 rgb = texture2D(AlbedoMap, TexCoords1.xy).rgb;


    if(intensity >= 0.0f && intensity < 0.2f)
        lightColor = col1;

    if(intensity >= 0.2f && intensity < 0.8f)
        lightColor = col2;

    if(intensity >= 0.8f)
        lightColor = col3;
	
	
	FragColor = vec4(rgb * lightColor, 1);

}