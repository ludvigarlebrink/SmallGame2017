#version 420


out vec4 FragColor;


uniform float T;


void main()
{
	float ratio =  1280.0 / 720;

	float x = gl_FragCoord.x / 1280.0;
	float y = gl_FragCoord.y / 720.0;
	x = x * ratio;
	vec3 center = vec3(0.5 * ratio, 0.5, 0.0);

	vec3 v1 = vec3(x, y, 0.0);

	float dist = distance(center, v1);

	if(T < 0.01)
	{
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else if(dist <= T)
	{
		float v = 1 -  clamp(T, 0.0, 1.0);
		FragColor = vec4(0.0, 0.0, 0.0, v);
	}
	else
	{
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}

}