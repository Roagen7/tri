#version 410 core

layout (vertices=3) out;

in vec3 col[];
in vec3 normal[];
in vec4 worldPos[];
in vec2 texPos[];
in vec3 tangent[];
in mat3 TBN[];
in vec4 ogPos[];

out vec3 _col[];
out vec2 _texPos[];
out vec3 _normal[];
out vec4 _worldPos[];
out vec3 _tangent[];
out mat3 _TBN[];
out vec4 _ogPos[];

void main(){
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    _texPos[gl_InvocationID] = texPos[gl_InvocationID];
    _normal[gl_InvocationID] = normal[gl_InvocationID];
    _worldPos[gl_InvocationID] = worldPos[gl_InvocationID];
    _tangent[gl_InvocationID] = tangent[gl_InvocationID];
    _ogPos[gl_InvocationID] = ogPos[gl_InvocationID];
    _col[gl_InvocationID] = col[gl_InvocationID];

    int level = 16;
    gl_TessLevelOuter[0] = level;
    gl_TessLevelOuter[1] = level;
    gl_TessLevelOuter[2] = level;
    gl_TessLevelInner[0] = level;
}
	