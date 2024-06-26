in vec3 vPos;
in vec2 vTexPos;

out vec2 texPos;

uniform mat4 projection;
uniform mat4 rotation;
uniform mat4 transform;

void main(){
    gl_Position = transform * vec4(vPos, 1.0);
    texPos = vTexPos;
}