#version 330 core 

in vec3 v_normal, v_position;
out vec4 color;

void main()
{
    vec3 light_position = vec3(0.0, 0.0, 0.0);
    vec3 light_color = vec3(0.0, 1.0, 1.0);

    vec3 light_direction = normalize(light_position - v_position);
    float diff = max(dot(v_normal, light_direction), 0.0);
    
    color = vec4(vec3(diff + 0.1) * light_color, 1.0);
}