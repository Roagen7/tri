#version 410 core

in vec3 gsColor;
in vec4 gsWorldPos;
in vec3 normal;
vec3 lightPos = vec3(0.0, 0.0, -4.0);
vec3 lightColor = vec3(1.0, 0.0, 0.0);

vec3 pointLight(vec3 clr){

   vec3 d = lightPos - gsWorldPos.xyz;
   float dist = length(d);
   float a = 1.0f;
   float b = 0.04f;
   float i = 1.0f /  (a * dist * dist + b * dist + 1.0f);
   float ambient = 0.1f;
   float specularLight = 0.5f;

   //diffuse
   vec3 normal = normalize(normal);
   vec3 lightDirection = normalize(d);
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   //specular
//    vec3 viewDirection = normalize(camPos - gsWorldPos);
//    vec3 reflectionDirection = reflect(-lightDirection, normal);
//    float specular = pow(max(dot(viewDirection, reflectionDirection),0.0f),16) * specularLight;

    float specular = 0;
   return  clr * lightColor * (diffuse * i + ambient + specular * i) ;
}

void main()
{
    //gl_FragColor = vec4(pointLight(gsColor), 1.0);
    gl_FragColor = vec4(normal, 1.0);
}