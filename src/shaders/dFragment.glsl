#version 330 core

out vec4 outFrag;

in vec3 outColor;

void main(void)
{
    outFrag = vec4(outColor, 1.0f);
}

