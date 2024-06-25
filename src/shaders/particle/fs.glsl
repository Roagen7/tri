in vec2 texPos;

uniform vec3 particleColor;
uniform sampler2D sprite;

out vec4 FragColor;
out vec4 BrightColor;

void main()
{
    FragColor = (texture(sprite, texPos) * vec4(particleColor, 1));
    BrightColor = FragColor;
}  