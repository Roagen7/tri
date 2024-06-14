#version 330 core

uniform vec3 uColor;
in vec3 cubemapPos;

uniform samplerCube skybox;

void main()
{
    gl_FragColor = texture(skybox, cubemapPos);
}