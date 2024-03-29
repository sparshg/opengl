#version 330 core 

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 ab;

out vec2 v_ab;
void main()
{
	v_ab = ab;
	gl_Position = vec4(pos, 1.0f);
}