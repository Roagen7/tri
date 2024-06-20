in vec2 texPos;

uniform sampler2D screenTexture;

void main()
{
    vec3 pixel = texture(screenTexture, texPos).rgb;
    gl_FragColor = vec4(1 - pixel.r, 1 - pixel.g, 1 - pixel.b, 1.0);
}