#version 330 core 

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
out vec3 fColor;

uniform mat4 u_Projection, u_Model;

void main()
{
	fColor = color;
	gl_Position = u_Projection * u_Model * position;
}