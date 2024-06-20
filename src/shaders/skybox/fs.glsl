uniform vec3 uColor;
uniform int solidColor;
in vec3 cubemapPos;

uniform samplerCube skybox;

out vec4 FragColor;
out vec4 BrightColor;

void main()
{   
    FragColor = texture(skybox, cubemapPos);
    if (solidColor == 1){
        FragColor = vec4(uColor, 1.0);
    }
    BrightColor = vec4(0,0,0, 1);
}