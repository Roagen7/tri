float shadowCalculation(vec4 sPos, sampler2D shadow){
    vec3 projCoords = sPos.xyz / sPos.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadow, projCoords.xy).r; 
    float currentDepth = projCoords.z;

    float bias = 0.005;
    float sha = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadow, 0);
    for(int x = -1; x <= 1; ++x)
    {
    for(int y = -1; y <= 1; ++y)
    {
        float pcfDepth = texture(shadow, projCoords.xy + vec2(x, y) * texelSize).r; 
        sha += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
    }    
    }
    sha /= 9.0;
    return sha;
}   