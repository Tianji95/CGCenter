#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColor;
uniform mat4 Model;
uniform mat4 CameraView;
uniform mat4 CameraProjection;
out vec3 fragmentColor;

void main()
{
    gl_Position = CameraProjection * CameraView * Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    fragmentColor = vertexColor;
}