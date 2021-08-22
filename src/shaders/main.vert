#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
uniform mat4 Model;
uniform mat4 CameraView;
uniform mat4 CameraProjection;
out vec3 fsnormal;
out vec2 fsuv;

void main()
{
    gl_Position = CameraProjection * CameraView * Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    fsnormal = normal;
    fsuv = uv;
}