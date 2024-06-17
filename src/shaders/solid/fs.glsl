#define MAX_POINT_LIGHTS 10
#define MAX_DIR_LIGHTS 3


// ------ textures -----
uniform int hasTexture;
uniform sampler2D texture0;

uniform int hasSpecularMap;
uniform sampler2D specularMap;

uniform int hasNormalMap;
uniform sampler2D normalMap;

// ------ textures end ----

// ------ shader config params -------


// ------ shader config params end -------

uniform int uNumPointLights;
uniform PointLight uPointLights[MAX_POINT_LIGHTS];
uniform int uNumDirLights;
uniform DirectionalLight uDirectionalLights[MAX_DIR_LIGHTS];


uniform float uDiffuse;
uniform float uSpecular;
uniform float uShininess;

uniform vec3 viewDir;
uniform vec3 ambientColor;
uniform float ambientIntensity;

in vec3 col;
in vec3 normal;
in vec4 worldPos;
in vec2 texPos;
in vec3 tangent;
in mat3 TBN;

void main()
{   
    vec3 outColor = vec3(0.0, 0.0, 0.0);
    outColor += ambientColor * ambientIntensity;

    float specular_val = uSpecular;
    if(hasSpecularMap == 1){
        specular_val = texture(specularMap, texPos).x;
    }

    vec3 normal_val = normal;
    if(hasNormalMap == 1){
        normal_val =texture(normalMap, texPos).xyz;
        normal_val = normal_val * 2 - 1;
        normal_val = normalize(TBN * normal_val);
    }
    
    for(int i = 0; i < uNumPointLights; i++){
        outColor +=  calcPointLight(uPointLights[i], normal_val, viewDir, worldPos, uShininess, specular_val, uDiffuse);
    }

    for(int i = 0; i < uNumDirLights; i++){
        outColor +=  calcDirLight(uDirectionalLights[i], normal_val, viewDir, uShininess, specular_val, uDiffuse);
    }

    if (hasTexture == 1){
        outColor *= texture(texture0, texPos).xyz;
    } else {
        outColor *= col;
    }

    outColor.x = min(outColor.x, 1.0);
    outColor.y = min(outColor.y, 1.0);
    outColor.z = min(outColor.z, 1.0);
    //texture(texture0, texPos).t
    //gl_FragColor = vec4(texture(texture0, texPos).xyz, 1.0);
    //gl_FragColor = vec4(texture(normalMap, texPos).xyz, 1.0);
    //gl_FragColor = vec4(normal_val, 1.0);
    gl_FragColor = vec4(outColor, 1.0);
}