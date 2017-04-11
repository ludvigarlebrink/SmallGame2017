#version 420
layout(triangles) in;
layout(trinagle_strip, max_vertices = 3) out;

void createGeom()
{
	for(int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();

}

void main()
{
	createGeom();
}