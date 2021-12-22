#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec2 uv2;
uniform mat4 Model;
uniform mat4 CameraView;
uniform mat4 CameraProjection;
uniform mat4 LightSpaceMatrix;
out vec3 fsnormal;
out vec2 fsuv;
out vec3 fsWorldPos;
out vec4 FragPosLightSpace;

void main()
{
    gl_Position = CameraProjection * CameraView * Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    fsnormal = normal;
    fsuv = uv;
    fsWorldPos = vec3(Model * vec4(aPos, 1.0));
    FragPosLightSpace = LightSpaceMatrix * vec4(fsWorldPos, 1.0f);
}