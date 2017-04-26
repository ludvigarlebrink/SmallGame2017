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
    if(outLife<10.0f){

    outPos=inPos+0.04*(normalize(inDir));

    outPos.z=0.0;
    outCol=inCol;
    outCol.a=inCol.a-0.001f;


    outDir=inDir;
    outLife=inLife+0.05f;
    outSize=inSize+4f;


    }

    if(outLife>30.0f){
        outPos=vec3(0.0, 15.0, 0.0);
        outCol.a=1.0;



        outCol.b=0.5;
        outLife=0.0f;
    }



    outSize=inSize;

}