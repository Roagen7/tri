in vec2 texPos;

uniform sampler2D screenTexture;

void main()
{
    vec3 pixel = texture(screenTexture, texPos).rgb;
    float y = pixel.r * 0.299 + pixel.g * 0.587 + pixel.b * 0.114;
    gl_FragColor = vec4(y, y, y, 1.0);
}