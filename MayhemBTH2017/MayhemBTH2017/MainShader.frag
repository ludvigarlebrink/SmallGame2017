#version 420

uniform vec3 Color;

out vec4 FragColor;

void main()
{

	
	FragColor = vec4(Color, 0);
	//FragColor = vec4(1,1,1,1);

}