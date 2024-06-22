float omniShadowCalculation(vec3 fragPos, vec3 lightPos, vec3 viewDir, float far_plane, samplerCube depthMap){
    vec3 gridSamplingDisk[20] = vec3[](
    vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
    vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
    vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
    vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
    vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
    );

    vec3 fragToLight = fragPos - lightPos;
    float currentDepth = length(fragToLight);
    float sha = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewDir - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int j = 0; j < samples; ++j){
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[j] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            sha += 1.0;
    }
    sha /= float(samples);
        
    return sha;
}