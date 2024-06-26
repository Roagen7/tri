in vec3 vPos;
in vec2 vTexPos;

out vec2 texPos;

uniform mat4 projection;
uniform mat4 rotation;
uniform mat4 transform;

uniform float screenWidth;
uniform float screenHeight;
uniform float width;
uniform float height;

void main(){
    vec2 scaledPos = vec2(vPos.x * width/screenWidth, vPos.y * height/screenHeight);
    gl_Position = transform * rotation * vec4(scaledPos, 0.0, 1.0);
    texPos = vTexPos;
}