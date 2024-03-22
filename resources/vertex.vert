#version 330 core 

layout(location = 0) in vec3 position;
out vec3 fragPos;

void main()
{
	fragPos = position;
	gl_Position = vec4(position.xyz, 1.0f);
}