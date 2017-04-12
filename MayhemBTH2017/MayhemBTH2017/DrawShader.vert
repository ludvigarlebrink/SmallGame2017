#version 420

in vec3 inPos;
in vec3 inDir;
in vec4 inCol;
in float inLife;
in float inSize;

out vec3 position1;
out vec3 direction1;
out vec4 color1;
out float life1;
out float size1;

void main()
{


	position1=inPos;
	direction1=(inDir);
	color1=inCol;
	life1=inLife;
	size1=inSize;
	


}

