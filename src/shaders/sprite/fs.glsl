in vec2 texPos;

uniform vec3 particleColor;
uniform sampler2D sprite;

out vec4 FragColor;
out vec4 BrightColor;

void main(){
    vec4 tex = texture(sprite, texPos);
    FragColor = tex;
    BrightColor = vec4(0.0, 0.0, 0.0, tex.a);
}  