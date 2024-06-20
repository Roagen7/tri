  
in vec2 texPos;
out vec4 FragColor;
out vec4 BrightColor;


uniform sampler2D colorAttachment0;
uniform sampler2D colorAttachment1;

uniform sampler2D ;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{             
    vec2 tex_offset = 1.0 / textureSize(colorAttachment1, 0); // gets size of single texel
    vec3 result = texture(colorAttachment1, texPos).rgb * weight[0]; // current fragment's contribution
    for(int i = 1; i < 5; ++i)
    {
        result += texture(colorAttachment1, texPos + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        result += texture(colorAttachment1, texPos - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
    }

    vec3 pixel = texture(colorAttachment0, texPos).rgb;
    FragColor = vec4(pixel + result, 1.0);
    BrightColor = vec4(result, 1.0);
}