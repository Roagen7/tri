#version 330 core

in vec3 color;
uniform vec3 uColor;


void main()
{
    gl_FragColor = vec4(uColor, 1.0);
}