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
	outCol=inCol;
	outCol.a=inCol.a-0.005f;
	outDir=inDir;
	outLife=inLife+0.05f;

	
	}

	if(outLife>10.0f){
		outPos=vec3(0.0, 0.0, 0.0);
		outCol.a=1.0;
		outLife=0.0f;
	}



	outSize=inSize;

}

