#version 420


in vec3 inPos;
in vec3 inDir;
in vec4 inCol;

in float inLife;
in float inSize;

out vec3 outPos;
out vec3 outDir;
out vec4 outCol;

out float outLife;
out float outSize;


void main()
{


	outPos=inPos+0.6*(normalize(inDir));
	outDir=inDir;
	outCol.g=inCol.g-0.02f;
	outLife=inLife;
	outSize=inSize;



}

