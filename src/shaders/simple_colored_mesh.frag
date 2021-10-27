#version 420 core
out vec4 FragColor;
in vec3 fscolor;

void main()
{
    FragColor = vec4(fscolor, 1.0);
} 