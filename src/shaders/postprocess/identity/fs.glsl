in vec2 texPos;

uniform sampler2D screenTexture;

void main()
{
    vec3 pixel = texture(screenTexture, texPos).rgb;

    gl_FragColor = vec4(pixel.r, pixel.g, pixel.b, 1.0);
}