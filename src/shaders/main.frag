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
uniform sampler2D shadow_map;

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

struct AreaLight {
    vec3 position;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define NR_POINT_LIGHTS 13
#define NR_SPOT_LIGHTS 13
#define NR_AREA_LIGHTS 13
uniform vec3 cameraPos;
uniform vec3 shadow_light_pos;
uniform int shadow_light_size;
uniform int shadow_type;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform AreaLight areaLights[NR_AREA_LIGHTS];
uniform Material material;

out vec4 FragColor;
in vec3 fsnormal;
in vec2 fsuv;
in vec3 fsWorldPos;
in vec4 FragPosLightSpace;

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

vec3 CalcAreaLight(AreaLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
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

float CalculateHardShadow(vec3 projCoords, float shadowBias)
{
    float closestDepth = texture(shadow_map, projCoords.xy).r;
    float shadow = projCoords.z - shadowBias > closestDepth  ? 1.0 : 0.0;
    return shadow;
}

float CalculatePCFShadow(vec3 projCoords, float shadowBias, int filterWidth)
{
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadow_map, 0);
    for(int x = -filterWidth; x <= filterWidth; ++x) {
        for(int y = -filterWidth; y <= filterWidth; ++y) {
            float pcfDepth = texture(shadow_map, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += projCoords.z - shadowBias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= ((filterWidth * 2 + 1) * (filterWidth * 2 + 1));
    return shadow;
}

float CalculatePCSSShadow(vec3 projCoords, float shadowBias)
{
    float shadow = 0.0;
    float avgBlockerDistance = 0;
    float blockCount = 0;
    vec2 texelSize = 1.0 / textureSize(shadow_map, 0);
    for (int x = -3; x < 3; x++) {
        for (int y = -3; y < 3; y++) {
            float z = texture(shadow_map, projCoords.xy + vec2(x, y) * texelSize).r;
            if (z < projCoords.z - shadowBias) {
                blockCount++;
                avgBlockerDistance += z;
            }
        }
    }
    if (blockCount > 0) {
        avgBlockerDistance = avgBlockerDistance / blockCount;
    }
    int filterWidth = 1;
    if(avgBlockerDistance != 0) {
        float penumbraWidth = (projCoords.z - avgBlockerDistance) / avgBlockerDistance;
        filterWidth = int(penumbraWidth * shadow_light_size / projCoords.z / 2);
    }
    return CalculatePCFShadow(projCoords, shadowBias,filterWidth);
}

float CalculateVSMShadow(vec3 projCoords, float shadowBias)
{
    float shadow = 0.0;
	vec2 depthvec = textureLod(shadow_map, projCoords.xy, 1).rg;
    float depth = depthvec.r;
    float depthsquare = depthvec.g;

    float variance = max(depthsquare - depth * depth, 0.00001f);
    float dist = depth - projCoords.z + shadowBias;
    if (0 < dist) {
        return 0.0f;
    }
    shadow = variance / (variance + dist*dist);
    return 1.0f - shadow;
}

float CalculateShadow(vec4 fragPosLightSpace, vec3 norm)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.x < 0.0f || projCoords.x > 1.0f || projCoords.y < 0.0f || projCoords.y > 1.0f) {
        return 0.0f;
    }
    vec3 lightDir = normalize(shadow_light_pos - fsWorldPos);
    float shadowBias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);
    float shadow = 0.0;
    if (shadow_type == 1) { // shadow hard
       shadow = CalculateHardShadow(projCoords, shadowBias);
    } else if (shadow_type == 2) { // PCF
        shadow = CalculatePCFShadow(projCoords, shadowBias, 1);
    } else if (shadow_type == 3) { // pcss todo: optimize sampling
        shadow = CalculatePCSSShadow(projCoords, shadowBias);
    } else if (shadow_type == 4) { // VSM shadow
        shadow = CalculateVSMShadow(projCoords, shadowBias);
    }
    return shadow;
}

void main()
{
    vec3 norm = normalize(fsnormal);
    vec3 viewDir = normalize(cameraPos - fsWorldPos);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);//CalcDirLight(dirLight, norm, viewDir);

    float shadow = CalculateShadow(FragPosLightSpace, norm);

    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        result += CalcPointLight(pointLights[i], norm, fsWorldPos, viewDir) * (1 - shadow);    
    }

    for(int i = 0; i < NR_SPOT_LIGHTS; i++){
        result += CalcSpotLight(spotLights[i], norm, fsWorldPos, viewDir) * (1 - shadow);    
    }

    for(int i = 0; i < NR_AREA_LIGHTS; i++){
        result += CalcAreaLight(areaLights[i], norm, fsWorldPos, viewDir) * (1 - shadow);    
    }

    FragColor = vec4(result, 1.0);
} 