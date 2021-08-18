#version 330 core

out vec4 FragColor;
in vec3 fsnormal;
in vec2 fsuv;

void main()
{
    FragColor = vec4(0.6f, 0.6f, 0.6f, 1.0f);
} 