uniform mat4 rotation;
uniform mat4 transform;
uniform mat4 projection;
in vec3 vPos;
in vec3 vNormal;

//in vec3 vCol;
out vec3 normal;


void main(){
    gl_Position = projection * transform * rotation * vec4(vPos, 1.0);
    normal = (rotation * vec4(vNormal, 1.0)).xyz;
}