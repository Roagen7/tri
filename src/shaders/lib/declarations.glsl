#version 410 core

struct PointLight {
    vec3 position;
    vec3 color;

    // attenuation coefficients
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

vec3 testFs(vec2 pt);
vec3 testGs(vec2 pt);

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec4 worldPos, float uShininess, float uSpecular, float uDiffuse);
vec3 calcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, float uShininess, float uSpecular, float uDiffuse);
vec2 parallaxMapping(vec2 texCoords, vec3 viewDir, sampler2D heightmap, float height_scale);
float shadowCalculation(vec4 sPos, sampler2D shadow);
float omniShadowCalculation(vec3 fragPos, vec3 lightPos, vec3 viewDir, float far_plane, samplerCube depthMap);
