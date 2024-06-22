uniform mat4 rotation;
uniform mat4 transform;
in vec3 vPos;
out vec3 ogPos;

void main(){
    gl_Position = transform * rotation * vec4(vPos, 1.0);
    ogPos = gl_Position.xyz;
}