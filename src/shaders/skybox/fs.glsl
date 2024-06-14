uniform vec3 uColor;
uniform int solidColor;
in vec3 cubemapPos;

uniform samplerCube skybox;

void main()
{   
    gl_FragColor = texture(skybox, cubemapPos);
    if (solidColor == 1){
        gl_FragColor = vec4(uColor, 1.0);
    }
}