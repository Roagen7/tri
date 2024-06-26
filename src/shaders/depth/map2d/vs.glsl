uniform mat4 rotation;
uniform mat4 transform;
uniform mat4 projection;
in vec3 vPos;

void main(){
    gl_Position = transform * rotation * vec4(vPos, 1.0);
}