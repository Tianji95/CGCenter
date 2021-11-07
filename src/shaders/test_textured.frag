#version 420 core
layout(binding = 0) uniform sampler2D texUnit;
out vec4 FragColor;
in vec3 fsnormal;
in vec2 fsuv;

void main()
{
    FragColor = texture2D(texUnit, fsuv);
} 