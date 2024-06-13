#version 330 core


uniform float uDiffuse;
uniform float uSpecular;
uniform float uShininess;

uniform vec3 viewDir;
uniform vec3 ambientColor;
uniform float ambientIntensity;

uniform int numPointLights;

in vec3 col;
in vec3 normal;
in vec4 worldPos;

vec3 lightPos = vec3(0.0, 0.0, -4.0);
vec3 lightColor = vec3(1.0, 1.0, 1.0);

vec3 ambient(){
    return vec3(1.0, 1.0, 1.0);
}

struct PointLight {
    vec3 position;
    vec3 color;

    // attenuation coefficients
    float constant;
    float linear;
    float quadratic;
};


vec3 calcPointLight(PointLight light){
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



void main()
{   
    PointLight light = PointLight(vec3(0.0, 0.0, -4.0), vec3(1.0, 1.0, 1.0), 1, 0.0, 0.5);


    vec3 outColor = vec3(0.0, 0.0, 0.0);
    outColor +=  calcPointLight(light);
    outColor += ambientColor * ambientIntensity;

    outColor *= col;

    outColor.x = min(outColor.x, 1.0);
    outColor.y = min(outColor.y, 1.0);
    outColor.z = min(outColor.z, 1.0);

    gl_FragColor = vec4(outColor, 1.0);
}