#version 420

layout(points) in;
layout (triangle_strip, max_vertices=4) out;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;



in vec3 position1[];
in vec3 direction1[];
in vec4 color1[];
in float life1[];
in float size1[];



out vec4 color2;


out vec3 finalCol;
out vec2 UV;

mat4 MV=M*V;
float particleSize=size1[0];
	
vec3 right = vec3(MV[0][0], 
					MV[1][0], 
					MV[2][0]);
	
vec3 up = vec3(MV[0][1], 
				MV[1][1], 
				MV[2][1]);


void CreateQuad(){
	for(int i=0; i<gl_in.length(); i++){
	
	color2=color1[0];

		//First vertex
		vec3 firstVert=position1[0].xyz-(right+up)*particleSize;

		gl_Position=P*V*vec4(firstVert+position1[i].xyz, 1.0);

		
		UV = vec2(0.0, 0.0);
		EmitVertex();
	
		//Second vertex
		vec3 secondVert=position1[0].xyz-(right-up)*particleSize;
	
		gl_Position=P*V*vec4(secondVert.xyz+position1[i].xyz, 1.0);


		UV = vec2(0.0, 1.0);
		EmitVertex();
	
		//Third vertex
		vec3 thirdVert=position1[0].xyz+(right-up)*particleSize;
	
		gl_Position=P*V*vec4(thirdVert+position1[i].xyz, 1.0);
	


		UV = vec2(1.0, 0.0);	
		EmitVertex();

		//Fourth vertex
		vec3 fourthVert=position1[0].xyz+(right+up)*particleSize;
		
		gl_Position=P*V*vec4(fourthVert+position1[i].xyz ,1.0);
	

		UV = vec2(1.0, 1.0);
		EmitVertex();
		
		EndPrimitive();
		
		}
	}

void main(){

	CreateQuad();


}

