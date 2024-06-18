#version 410 core

uniform mat4 transform;
uniform mat4 projection;
in vec3 vPos;
in vec3 vCol;

out vec3 vsColor;
out vec4 worldPos;

void main(){
    gl_Position = projection * transform * vec4(vPos, 1.0);
    worldPos = transform * vec4(vPos, 1.0);
    vsColor = vec3(1.0, 1.0, 1.0);
}