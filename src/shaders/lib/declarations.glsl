#version 330 core

struct PointLight {
    vec3 position;
    vec3 color;

    // attenuation coefficients
    float constant;
    float linear;
    float quadratic;
};

vec3 testFs(vec2 pt);
vec3 testGs(vec2 pt);

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec4 worldPos, float uShininess, float uSpecular, float uDiffuse);