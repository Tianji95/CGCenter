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

struct Material {
    vec3 colorDiffuse;
    vec3 colorSpecular;
    vec3 colorAmbiend;
    vec3 colorEmissive;
    vec3 colorTransparent;
    float opacity;
    float shininess;
    float shininessStrength;
    float reflection;
    float refraction;
    float transparentFactor;
    int shadingModel;
    int blendFunc;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define NR_POINT_LIGHTS 4
uniform vec3 cameraPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

out vec4 FragColor;
in vec3 fsnormal;
in vec2 fsuv;
in vec3 fsWorldPos;

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse, fsuv));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse, fsuv));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular, fsuv));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse, fsuv));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse, fsuv));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular, fsuv));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse, fsuv));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse, fsuv));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular, fsuv));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(fsnormal);
    vec3 viewDir = normalize(cameraPos - fsWorldPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        result += CalcPointLight(pointLights[i], norm, fsWorldPos, viewDir);    
    }

    result += CalcSpotLight(spotLight, norm, fsWorldPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
} 