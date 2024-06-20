uniform mat4 rotation;
uniform mat4 transform;
uniform mat4 projection;
uniform vec3 uColor;
uniform mat4 shadowSpaceMatrix;

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexPos;
in vec3 vTangent;

out vec3 col;
out vec3 normal;
out vec4 worldPos;
out vec2 texPos;
out vec3 tangent;
out mat3 TBN;
out vec4 ogPos;
out vec4 shadowSpacePos;

void main(){
    ogPos = vec4(vPos, 1.0);
    gl_Position = projection * transform * rotation * ogPos;
    col = uColor;
    texPos = vTexPos;
    tangent = vTangent;
    normal = (rotation * vec4(vNormal, 1.0)).xyz;
    worldPos = transform * rotation * vec4(vPos, 1.0);

    // ---- TBN matrix calculation for tangent space maps ---
    
    vec3 T = normalize(vec3(rotation * vec4(vTangent,   0.0)));
    vec3 B = normalize(vec3(rotation * vec4(cross(vTangent, vNormal), 0.0)));
    vec3 N = normalize(normal);

    shadowSpacePos = shadowSpaceMatrix * transform * rotation * ogPos;

    TBN = mat3(T, B, N);
}