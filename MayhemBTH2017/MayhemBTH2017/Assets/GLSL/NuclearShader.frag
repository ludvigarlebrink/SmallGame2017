#version 420


out vec4 FragColor;

uniform float Time;
uniform vec2 Resolution;
uniform float Alpha;


vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

float rand(vec2 n) {
    return fract(sin(cos(dot(n, vec2(12.9898,12.1414)))) * 83758.5453);
}

float noise(vec2 n) {
    const vec2 d = vec2(0.0, 1.0);
    vec2 b = floor(n), f = smoothstep(vec2(0.0), vec2(1.0), fract(n));
    return mix(mix(rand(b), rand(b + d.yx), f.x), mix(rand(b + d.xy), rand(b + d.yy), f.x), f.y);
}

float fbm(vec2 n) {
    float total = 0.0, amplitude = 1.0;
    for (int i = 0; i <5; i++) {
        total += noise(n) * amplitude;
        n += n*1.7;
        amplitude *= 0.47;
    }
    return total;
}

void main() {

    const vec3 c1 = vec3(0.5, 1.0, 0.1);
    const vec3 c2 = vec3(0.0, 1.0, 0.0);
    const vec3 c3 = vec3(0.2, 1.0, 0.7);
    const vec3 c4 = vec3(0.0, 1.0, 1.0);
    const vec3 c5 = vec3(0.1);
    const vec3 c6 = vec3(0.9);

    vec2 speed = vec2(1.2, 0.1);
    float shift = 1.0;
    float alpha = 1.0;
    
    //change the constant term for all kinds of cool distance versions,
    //make plus/minus to switch between 
    //ground fire and fire rain!
	float dist = 16.8-sin(Time*0.4)/51.89;
    
    vec2 p = gl_FragCoord.xy * dist / Resolution.xx;
    p.x -= Time/1.1;
    float q = fbm(p - Time * 0.01+1.0*sin(Time)/10.0);
    float qb = fbm(p - Time * 0.002+0.1*cos(Time)/5.0);
    float q2 = fbm(p - Time * 0.44 - 5.0*cos(Time)/7.0) - 6.0;
    float q3 = fbm(p - Time * 0.9 - 10.0*cos(Time)/30.0)-30.0;
    float q4 = fbm(p - Time * 2.0 - 2.0*sin(Time)/20.0)+2.0;
    q = (q + qb - .4 * q2 -2.0*q3  + .6*q4)/3.8;
    vec2 r = vec2(fbm(p + q /2.0 + Time * speed.x - p.x - p.y), fbm(p + q - Time * speed.y));
    vec3 c = mix(c1, c2, fbm(p + r)) + mix(c3, c4, r.x) - mix(c5, c6, r.y);
    vec3 color = vec3(c * cos(shift * gl_FragCoord.y / Resolution.y));
    color += .05;
    color.r *= .8;
    vec3 hsv = rgb2hsv(color);
    hsv.y *= hsv.z  * 1.1;
    hsv.z *= hsv.y * .3;
    hsv.y = (0.2-hsv.z*.9)*3.20;
    color = hsv2rgb(hsv);

	FragColor = vec4(color.x, clamp(color.y * 2, 0, 1), color.z, Alpha);

}
