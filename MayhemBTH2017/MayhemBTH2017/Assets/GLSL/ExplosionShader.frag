#version 420


out vec4 FragColor;

uniform float ScreenWidth;
uniform float ScreenHeight;
uniform float T;


float average(float c)
{
	if(c < 0.3)
	{
		return 0.0;
	}
	else if(c >= 0.3 && c < 0.7)
	{
		return 0.7;
	}
	else
	{
		return 1.0;
	}
}

float snoise(vec3 uv, float res)
{
	const vec3 s = vec3(1e0, 1e2, 1e3);
	
	uv *= res;
	
	vec3 uv0 = floor(mod(uv, res))*s;
	vec3 uv1 = floor(mod(uv+vec3(1.), res))*s;
	
	vec3 f = fract(uv); f = f*f*(3.0-2.0*f);

	vec4 v = vec4(uv0.x+uv0.y+uv0.z, uv1.x+uv0.y+uv0.z,
		      	  uv0.x+uv1.y+uv0.z, uv1.x+uv1.y+uv0.z);

	vec4 r = fract(sin(v*1e-1)*1e3);
	float r0 = mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y);
	
	r = fract(sin((v + uv1.z - uv0.z)*1e-1)*1e3);
	float r1 = mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y);
	
	return mix(r0, r1, f.z)*2.-1.;
}


void main( void ) {	
	if(T >= 1.0 && T < 2.0)
	{
		FragColor = vec4(1.0, 1.0, 1.0, 1.0f);
	}
	else if(T >= 2.0)
	{
		float k = (2.0 - T) * 0.2;
		float t = 1.0 + k;
		FragColor = vec4(1.0, 1.0, 1.0, t);
	}
	else
	{
		float time = T;
		vec2 resolution = vec2(ScreenWidth, ScreenHeight);
		vec2 p = gl_FragCoord.xy / resolution.xy;

		float ratio = ScreenWidth / ScreenHeight;

		float t = 1.0 - T;

		p.x = (p.x - 0.0 / resolution.x - 0.5) * t * (ratio / 2);
		p.y = (p.y + 0.0 / resolution.y - 0.5) * t;
		p.y = -p.y;
		
		p.x*=resolution.x/resolution.y;			
				  	
		float color = 3.0 - (6.*length(p));		
		
		vec3 coord = vec3(atan(p.x,p.y)/6.2832, length(p)*0.4, 0.5);
		
		for(int i = 1; i <= 7; i++){
			float power = pow(2.0, float(i));
			color += (1.5 / power) * snoise(coord + vec3(0.,-time*.05, time*0.01), power*16.);
		}
		
		vec3 col = vec3( color, pow(max(color,0.),2.)*0.4, pow(max(color,0.),3.)*0.15);

		col = vec3(average(col.x), average(col.y), average(col.z));

		if(col.x < 0.001f && col.y < 0.001f && col.z < 0.001f)
		{
			FragColor = vec4(col, 0.0f);
		}
		else
		{
			FragColor = vec4(col.x, col.y, col.z, 1.0f);
		}
	}
}