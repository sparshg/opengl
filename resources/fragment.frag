#version 330 core 

in vec3 fragPos;
out vec4 color;

uniform float u_Time;

int maxIterations = 100;

vec3 colors[16] = vec3[](
    vec3(11, 15, 20) / 255.0,
    vec3(25, 7, 26) / 255.0,
    vec3(9, 1, 47) / 255.0,
    vec3(4, 4, 73) / 255.0,
    vec3(0, 7, 100) / 255.0,
    vec3(12, 44, 138) / 255.0,
    vec3(24, 82, 177) / 255.0,
    vec3(57, 125, 209) / 255.0,
    vec3(134, 181, 229) / 255.0,
    vec3(211, 236, 248) / 255.0,
    vec3(241, 233, 191) / 255.0,
    vec3(248, 201, 95) / 255.0,
    vec3(255, 170, 0) / 255.0,
    vec3(204, 128, 0) / 255.0,
    vec3(153, 87, 0) / 255.0,
    vec3(106, 52, 3) / 255.0
);

vec3 iterateMandelbrot(vec2 coord){
	vec2 z = vec2(0,0);
	for(int i=0;i<maxIterations;i++){
		z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y) + coord;
		if(length(z) > 2) return colors[i % 16];
	}
	return vec3(0.0f);
}

void main()
{
    vec2 pos = vec2(fragPos.x / 0.75, fragPos.y) / (pow(2, u_Time) + 1.0f) - vec2(0.996f, -0.3f);
    color = vec4(iterateMandelbrot(pos), 1.0f);
}