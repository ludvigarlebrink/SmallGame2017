#version 420

out vec4 FragColor;
in vec3 finalCol;
in vec3 UV;

in vec3 color2;


void main()
{

	
	FragColor = vec4(color2, 1.0);
	

}