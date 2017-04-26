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

highp float rand(vec2 co)
{
    highp float a = 182.9898;
    highp float b = 878.233;
    highp float c = 884.53357453;
    highp float dt= dot(co.xy ,vec2(a,b));
    highp float sn= mod(dt, 737673.14);
    return fract(sin(sn) * c);
}
void main()
{
    uint seed = uint(outLife * 10000.0) + uint(gl_VertexID);
	outPos=inPos-0.00006f*pow(seed,inLife/30)*((vec2(rand(vec2(inLife, -10000)), rand(vec2(5, -500)))));

	outDir=inDir;
	outCol=inCol;
	outVel=inVel;
	outLife=inLife+0.05f;
	outPos.y=normalize(fract(sin(seed*acc)*-0.5));

	

	
}

