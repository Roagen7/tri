#define MAX_POINT_LIGHTS 10
#define MAX_DIR_LIGHTS 3
#define MAX_CASCADES 16


uniform int flatColor;

// ------ textures -----
uniform int hasTexture;
uniform sampler2D texture0;

uniform int hasSpecularMap;
uniform sampler2D specularMap;

uniform int hasNormalMap;
uniform sampler2D normalMap;

uniform int hasHeightMap;
uniform sampler2D heightMap;
uniform float height_scale;


uniform int hasShadow;
uniform sampler2DArray shadowMap[MAX_DIR_LIGHTS];
uniform mat4 shadowSpaceMatrix[MAX_DIR_LIGHTS * MAX_CASCADES];
uniform int cascadeCount;
uniform float cascadePlaneDistances[MAX_CASCADES];

uniform samplerCube shadowCube[MAX_POINT_LIGHTS];
uniform float pointLightFarPlane;

// ------ textures end ----

uniform int uNumPointLights;
uniform PointLight uPointLights[MAX_POINT_LIGHTS];
uniform int uNumDirLights;
uniform DirectionalLight uDirectionalLights[MAX_DIR_LIGHTS];


uniform float uDiffuse;
uniform float uSpecular;
uniform float uShininess;

uniform vec3 viewDir;
uniform vec3 viewPos;
uniform vec3 ambientColor;
uniform float ambientIntensity;

uniform mat4 projection;

in vec3 col;
in vec3 normal;
in vec4 worldPos;
in vec2 texPos;
in vec3 tangent;
in mat3 TBN;
in vec4 ogPos;
in mat4 model;


out vec4 FragColor;
out vec4 BrightColor;


int selectShadowLayer(vec4 projectedCoord){
    float depthValue = projectedCoord.z;
        
    int layer = -1;
    for (int i = 0; i < cascadeCount; ++i){
        if (depthValue < cascadePlaneDistances[i]){
            layer = i;
            break;
        }
    }
    if (layer == -1){
        layer = cascadeCount - 1;
    }
    return layer;
}


void main()
{   
    if(flatColor == 1){
        FragColor = vec4(col, 1.0);
        BrightColor = vec4(0,0,0,1);
        return ;
    }
    vec3 outColor = vec3(0.0, 0.0, 0.0);
    outColor += ambientColor * ambientIntensity;

    vec2 texCoords_val = texPos;
    if(hasHeightMap == 1){
        texCoords_val = parallaxMapping(texPos, TBN * viewDir, heightMap, height_scale);
    }

    float specular_val = uSpecular;
    if(hasSpecularMap == 1){
        specular_val = texture(specularMap, texCoords_val).x;
    }

    vec3 normal_val = normal;
    if(hasNormalMap == 1){
        normal_val =texture(normalMap, texCoords_val).xyz;
        normal_val = normal_val * 2 - 1;
        normal_val = normalize(TBN * normal_val);
    }
    
    for(int i = 0; i < uNumPointLights; i++){
        outColor +=  calcPointLight(uPointLights[i], normal_val, viewDir, worldPos, uShininess, specular_val, uDiffuse);
    }

    for(int i = 0; i < uNumDirLights; i++){
        outColor +=  calcDirLight(uDirectionalLights[i], normal_val, viewDir, uShininess, specular_val, uDiffuse);
    }
    
    float sh = 1.0;
    int layer;
    for(int i = 0; i < uNumDirLights; i++){
        layer = selectShadowLayer(projection * worldPos);
        float bias = max(0.05 * (1.0 - dot(normal_val, uDirectionalLights[i].direction)), 0.005);
        bias *= 1 / (cascadePlaneDistances[layer] * 0.5f);
        
        vec4 shadowSpacePos = shadowSpaceMatrix[i * MAX_CASCADES + layer] * worldPos;
        sh = min(sh, shadowCalculation(shadowSpacePos, shadowMap[i], layer, bias));
    }

    for(int i = 0; i < uNumPointLights; i++){
        float s = omniShadowCalculation(worldPos.xyz, uPointLights[i].position, viewDir, pointLightFarPlane, shadowCube[i]);
        sh = min(sh, s);
    }

    if(hasShadow == 1){
        outColor -= outColor * sh;
    }
    
    if (hasTexture == 1){
        outColor *= texture(texture0, texCoords_val).xyz;
    } else {
        outColor *= col;
    }

    outColor.x = min(outColor.x, 1.0);
    outColor.y = min(outColor.y, 1.0);
    outColor.z = min(outColor.z, 1.0);

    float alpha = 1.0;
    if (hasTexture == 1){
        alpha = texture(texture0, texCoords_val).a;
    }
    FragColor = vec4(outColor, alpha);

    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.8){
        BrightColor = vec4(FragColor.rgb,0);
    } else {
        BrightColor = vec4(0, 0, 0,alpha);
    } 
}