#version 410 core

layout (triangles, equal_spacing, ccw) in;

uniform mat4 rotation;
uniform mat4 transform;
uniform mat4 projection;

uniform sampler2D heightMap;

uniform float heightScale;

in vec3 _col[];
in vec4 _ogPos[];
in vec2 _texPos[];
in vec3 _normal[];
in vec4 _worldPos[];
in vec3 _tangent[];
in mat3 _TBN[];

out vec3 col;
out vec3 normal;
out vec4 worldPos;
out vec2 texPos;
out vec3 tangent;
out mat3 TBN;


vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
} 

void main(){     
    
    texPos = interpolate2D(_texPos[0], _texPos[1], _texPos[2]);
    normal = interpolate3D(_normal[0], _normal[1], _normal[2]);
    tangent = interpolate3D(_tangent[0], _tangent[1], _tangent[2]);
    vec3 interpolatedPos = interpolate3D(_ogPos[0].xyz, _ogPos[1].xyz, _ogPos[2].xyz);
    
    interpolatedPos.y += texture(heightMap, texPos).r * heightScale;
    col = interpolate3D(_col[0], _col[1], _col[2]) * texture(heightMap, texPos).r;

    gl_Position = projection * transform * rotation * vec4(interpolatedPos, 1.0);
}