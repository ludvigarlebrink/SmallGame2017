#version 420


in vec3 TexCoords1;
in vec3 Normal1;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D t;

void main()
{
	FragColor = texture2D(t, vec2(TexCoords1.x, -TexCoords1.y));
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}