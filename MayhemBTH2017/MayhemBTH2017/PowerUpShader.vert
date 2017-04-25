#version 420

layout(location = 0) in vec2 Position;



uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 UV;

void main()
{


	float x=Position.x-0.5*84;
	float y=Position.y-0.5*48;
	gl_Position=P*V*vec4(x,y, 0, 1);

}

