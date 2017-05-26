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

	int seed=gl_VertexID;

	outPos=inPos+0.2*(normalize(inDir));
	outDir=inDir;
	outCol=inCol;
	outLife=inLife;
	outSize=inSize+0.4f*sin(seed);
	outCol.a=inCol.a-0.05f;


}

