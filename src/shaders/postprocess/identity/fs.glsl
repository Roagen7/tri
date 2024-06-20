in vec2 texPos;

uniform sampler2D colorAttachment0;
uniform sampler2D colorAttachment1;

void main()
{
    vec3 pixel = texture(colorAttachment0, texPos).rgb;
    gl_FragColor = vec4(pixel.r, pixel.g, pixel.b, 1.0);
}