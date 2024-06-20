in vec3 color;
uniform vec3 uColor;

out vec4 FragColor;
out vec4 BrightColor;

void main()
{
    FragColor = vec4(uColor, 1.0);
    BrightColor = vec4(uColor, 1.0);
}