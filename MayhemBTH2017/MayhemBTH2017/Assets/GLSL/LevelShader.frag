#version 420

in vec3 TexCoords1;
in vec3 Normal1;
in vec3 FragPos;
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

	//vec2 spriteUV = selectedUV.xy + (TexCoords1 * selectedUV.zw);
	vec3 ambient = vec3(1,1,1) * vec3(0.5,0.5,0.5);

	vec3 norm = normalize(Normal1);
	vec3 lightDir = normalize(V[3].xyz - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = vec3(1,1,1) * (diff * vec3(0.5,0.5,0.5));

	vec3 viewDir = normalize(V[3].xyz - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 20);
	vec3 specular = vec3(1,1,1) * (spec * vec3(0.5,0.5,0.5));

	vec3 result = ambient + diffuse + specular;


	FragColor = texture2D(t, vec2(TexCoords1.x, -TexCoords1.y)) * vec4(result, 1.0);
}