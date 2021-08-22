#version 420 core
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_ambient;
uniform sampler2D texture_emissive;
uniform sampler2D texture_height;
uniform sampler2D texture_normals;
uniform sampler2D texture_shininess;
uniform sampler2D texture_opacity;
uniform sampler2D texture_displacement;
uniform sampler2D texture_lightmap;
uniform sampler2D texture_reflection;
uniform sampler2D texture_basecolor;
uniform sampler2D texture_normal_camera;
uniform sampler2D texture_emission_color;
uniform sampler2D texture_metalness;
uniform sampler2D texture_diffuse_roughness;
uniform sampler2D texture_ambient_occlusion;

uniform vec3 colorDiffuse;
uniform vec3 colorSpecular;
uniform vec3 colorAmbiend;
uniform vec3 colorEmissive;
uniform vec3 colorTransparent;
uniform float opacity;
uniform float shininess;
uniform float shininessStrength;
uniform float reflection;
uniform float refraction;
uniform float transparentFactor;
uniform int shadingModel;
uniform int blendFunc;

out vec4 FragColor;
in vec3 fsnormal;
in vec2 fsuv;

void main()
{
    // FragColor = vec4(fsuv,0.0f, 1.0f);
    FragColor = texture2D(texture_diffuse, fsuv);
} 