
uniform mat4 rotation;
uniform mat4 transform;
uniform mat4 projection;
uniform vec3 uColor;

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexPos;
out vec3 col;
out vec3 normal;
out vec4 worldPos;
out vec2 texPos;


void main(){
    gl_Position = projection * transform * rotation * vec4(vPos, 1.0);
    col = uColor;
    texPos = vTexPos;
    normal = (rotation * vec4(vNormal, 1.0)).xyz;
    worldPos = transform * rotation * vec4(vPos, 1.0);
}