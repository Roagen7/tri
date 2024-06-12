#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

in vec3 vsColor[];
in vec4 worldPos[];

out vec3 gsColor;
out vec4 gsWorldPos;
out vec3 normal;



void main() {  
    vec3 norm = cross(
        worldPos[1].xyz - worldPos[0].xyz, 
        worldPos[2].xyz - worldPos[0].xyz
        );

    gl_Position = gl_in[0].gl_Position;
    gsColor = vsColor[0];
    gsWorldPos = worldPos[0];
    normal = norm;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    gsColor = vsColor[1];
    gsWorldPos = worldPos[1];
    normal = norm;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    gsColor = vsColor[2];
    gsWorldPos = worldPos[2];
    normal = norm;
    EmitVertex();
    //EndPrimitive();

}