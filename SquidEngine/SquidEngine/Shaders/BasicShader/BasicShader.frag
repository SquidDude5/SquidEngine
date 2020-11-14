#version 330 core
out vec4 FragColor;

#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 8
#define MAX_DIRECTIONAL_LIGHTS 8

#define MAX_DIFFUSE_MAPS 8 
#define MAX_SPECULAR_MAPS 8

struct Material {
    int numDiffuseMaps;
    int numSpecularMaps;
    float reflectivity;
    sampler2D diffuseMaps[MAX_DIFFUSE_MAPS];
    sampler2D specularMaps[MAX_SPECULAR_MAPS];
    
}; 


struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float linearFallOff;
    float quadraticFallOff;
}; 


struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float linearFallOff;
    float quadraticFallOff;
    float innerCutOff;
    float outerCutOff;
}; 


struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 


uniform bool enabledPointLights[MAX_POINT_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform bool enabledSpotLights[MAX_SPOT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform bool enabledDirectionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

uniform Material material;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 texUV;

uniform vec3 cameraPos;


void main() {
    vec3 mergedTexture = vec3(1,1,1);
    for (int i=0; i < material.numDiffuseMaps; ++i){ mergedTexture *= texture(material.diffuseMaps[i], texUV).xyz; }
    FragColor = vec4(mergedTexture,1);
} 


