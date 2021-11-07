#version 420 core
layout (location = 0) in vec3 aPos;
uniform mat4 Model;
uniform mat4 LightSpaceMatrix;

void main()
{
    gl_Position = LightSpaceMatrix * Model * vec4(aPos, 1.0f);
}