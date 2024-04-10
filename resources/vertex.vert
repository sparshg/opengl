#version 330 core 

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
out vec3 v_normal, v_position;

uniform mat4 u_Projection, u_View, u_Model;

void main()
{
	v_position = (u_Model * position).xyz;
	v_normal = normalize(mat3(transpose(inverse(u_Model))) * normal);
	gl_Position = u_Projection * u_View * u_Model * position;
}