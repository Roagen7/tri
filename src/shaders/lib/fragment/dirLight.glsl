vec3 calcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, float uShininess, float uSpecular, float uDiffuse){
    vec3 lightDir = light.direction;
    float diff = max(dot(normalize(normal), lightDir), 0.0);
    vec3 reflectDir = normalize(reflect(lightDir, normalize(normal)));
    float spec = pow(max(dot(normalize(viewDir), reflectDir), 0.0), uShininess);
    return light.color * (diff * uDiffuse + spec * uSpecular) * light.intensity;
}