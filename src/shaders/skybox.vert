#version 420 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 Model;
uniform mat4 CameraView;
uniform mat4 CameraProjection;

void main()
{
    TexCoords = aPos;
    vec4 pos = CameraProjection * CameraView * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  