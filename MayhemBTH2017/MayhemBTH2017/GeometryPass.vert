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
	if(outLife<10.0f){
	outPos=inPos+0.06f*normalize(inDir);
	outCol.a=inCol.a-outLife;
	outCol.x=inCol.x;
	outCol.y=inCol.y;
	outCol.z=inCol.z;
	outDir=inDir;
	outLife=inLife+0.05f;
	outSize=inSize;
	}


	if(outLife>10.0f){
		outPos=inPos;
		outLife=0.0f;
	}


}

