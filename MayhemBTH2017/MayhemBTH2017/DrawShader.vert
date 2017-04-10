#version 420

in vec3 inPos;
in vec3 inDir;
in vec3 inCol;
in float inVel;
in float inLife;


out vec3 position1;
out vec3 dir1;
out vec3 color1;
out float vel1;
out float life1;



out int seed;
void main()
{


	position1=inPos;
	dir1=inDir;
	color1=inCol;
	vel1=inVel;
	life1=inLife;


}

