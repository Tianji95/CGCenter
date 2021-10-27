#version 420 core
layout(binding = 0) uniform sampler2D texUnit;
out vec4 FragColor;
in vec3 fsnormal;
in vec2 fsuv;

void main()
{
    // FragColor = vec4(fsuv,0.0f, 1.0f);
    FragColor = texture2D(texUnit, fsuv);
} 