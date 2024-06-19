in vec3 vPos;
in vec3 vNormal;
in vec2 vTexPos;
in vec3 vTangent;

out vec2 texPos;

void main()
{
    gl_Position = vec4(2 * vPos.x, 2 * vPos.z, 0.0, 1.0); 
    texPos = vPos.xz + vec2(0.5,0.5);
}  