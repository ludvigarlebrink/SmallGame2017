#version 420

layout(location = 0) in vec2 Position;



uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 UV;

void main()
{


	float x=Position.x;
	float y=Position.y;
	gl_Position=P*V*M*vec4(x,y, 0, 1);

}

