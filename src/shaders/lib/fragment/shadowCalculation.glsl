float shadowCalculation(vec4 sPos, sampler2DArray shadow, int layer, float bias){
    vec3 projCoords = sPos.xyz / sPos.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadow, vec3(projCoords.xy, layer)).r; 
    float currentDepth = projCoords.z;

    float sha = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadow, 0).xy;
    for(int x = -1; x <= 1; ++x){
        for(int y = -1; y <= 1; ++y){
            float pcfDepth = texture(shadow, vec3(projCoords.xy + vec2(x, y) * texelSize, layer)).r; 
            sha += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    if(projCoords.z > 1.0) return 0.0;
    sha /= 9.0;
    return sha;
}   