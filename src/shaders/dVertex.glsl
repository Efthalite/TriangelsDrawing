#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inCol;


out vec3 outColor;
uniform float u_Time;
uniform mat4 u_Transform;

float Ranged()
{
    return (cos(u_Time) + sin(u_Time)) * 0.5f;
}

void main(void)
{
    gl_Position =  u_Transform * vec4(inPos, 1.0f);
    outColor = vec3(1.0f * Ranged(), 0.8f * Ranged()*0.4f, 0.8f * Ranged() * 0.75f);

    //outColor = inCol;
}