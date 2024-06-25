in vec3 vPos;
in vec2 vTexPos;

out vec2 texPos;

uniform mat4 projection;
uniform mat4 rotation;
uniform mat4 transform;
uniform vec3 offset;

uniform float scale;
uniform vec3 cameraUp;
uniform vec3 cameraRight;

uniform vec4 color;


void main(){
    vec4 centerPos = transform * rotation * vec4(offset, 1.0);
    gl_Position = projection * vec4(centerPos.xyz + normalize(cameraUp) * vPos.y * scale + normalize(cameraRight) * vPos.x * scale, 1.0);
    texPos = vTexPos;
}