#version 330 core

uniform mat4 rotation;
uniform mat4 transform;
uniform mat4 projection;
in vec3 vPos;
out vec3 cubemapPos;

void main(){
    gl_Position = projection * transform * rotation * vec4(vPos, 1.0);
    cubemapPos = vPos;
}