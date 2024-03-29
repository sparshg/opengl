#version 330 core 

in vec2 v_ab;
out vec4 color;

void main()
{
    color = vec4(v_ab, 0.0, 1.0);
}