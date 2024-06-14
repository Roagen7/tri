#define MAX_POINT_LIGHTS 10


// ------ textures -----
uniform int hasTexture;
uniform sampler2D texture0;

// ------ textures end ----

// ------ shader config params -------
uniform int hasSpecularMap;
uniform int hasDiffuseMap;
// ------ shader config params end -------

uniform int uNumPointLights;
uniform PointLight uPointLights[MAX_POINT_LIGHTS];

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

void main()
{   
    vec3 outColor = vec3(0.0, 0.0, 0.0);
    outColor += ambientColor * ambientIntensity;

    for(int i = 0; i < uNumPointLights; i++){
        if(i > uNumPointLights) {
            continue;
        }

        outColor +=  calcPointLight(uPointLights[i], normal, viewDir, worldPos, uShininess, uSpecular, uDiffuse);
    }

    if (hasTexture == 1){
        outColor *= texture(texture0, texPos).xyz;
    } else {
        outColor *= col;
    }

    outColor.x = min(outColor.x, 1.0);
    outColor.y = min(outColor.y, 1.0);
    outColor.z = min(outColor.z, 1.0);
    gl_FragColor = vec4(outColor, 1.0);

    testFs(vec2(0.0, 0.0));
}