#version 420


in vec3 inPos;
in vec3 inDir;
in vec3 inCol;

in float inVel;
in float inLife;


out vec3 outPos;
out vec3 outDir;
out vec3 outCol;

out float outVel;
out float outLife;


void main()
{
	outPos=inPos+inLife*inDir;
	outDir=inDir;
	outCol=inCol;
	outVel=inVel;
	outLife=sin(sin(inLife)+05f);

}

