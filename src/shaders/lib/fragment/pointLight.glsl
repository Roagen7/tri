vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec4 worldPos, float uShininess, float uSpecular, float uDiffuse){
    //-------------------attenuation-------------------------------
    float distance    = length(light.position - worldPos.xyz);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    


    //-------------------PHONG-------------------------------
    vec3 lightDir = normalize(light.position - worldPos.xyz);
    // diffuse
    float diff = max(dot(normalize(normal), lightDir), 0.0);
    // // specular
    vec3 reflectDir = normalize(reflect(lightDir, normalize(normal)));
    float spec = pow(max(dot(normalize(viewDir), reflectDir), 0.0), uShininess);
    //float spec = max(dot(viewDir, reflectDir), 0.0);

    //-------------------maps-------------------------------    
    // TODO: add specular and diffuse map support

    return attenuation * light.color * (diff * uDiffuse + spec * uSpecular);
}