#version 330 core


uniform float uDiffuse;
uniform float uSpecular;

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
    vec3 lightDir = normalize(light.position - worldPos.xyz);

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // // specular
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);


    // attenuation
    float distance    = length(light.position - worldPos.xyz);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    //vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    //vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    //ambient  *= attenuation;
    //diffuse  *= attenuation;
    //specular *= attenuation;
    //return (ambient + diffuse + specular);

    // remember to add material diffuse property
    vec3 diffuse = light.color * diff * uDiffuse;

    return attenuation * diffuse;
}



void main()
{   
    PointLight light = PointLight(vec3(0.0, 0.0, -4.0), vec3(1.0, 1.0, 1.0), 1, 0.0, 0.5);


    vec3 outColor = vec3(0.0, 0.0, 0.0);
    outColor +=  calcPointLight(light);
    outColor += ambientColor * ambientIntensity;

    outColor *= col;


    gl_FragColor = vec4(outColor, 1.0);
}