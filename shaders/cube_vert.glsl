#version 330 core

layout (location = 0) in uvec3 coord3d;
layout (location = 1) in vec3 v_colour;
layout (location = 2) in uint v_normal_index;

uniform mat4 model;
uniform mat4 vp;
uniform mat4 normal_matrix;

vec3 normals[6] = vec3[6](
    vec3(-1.0f,  0.0f,  0.0f),
    vec3( 1.0f,  0.0f,  0.0f),
    vec3( 0.0f, -1.0f,  0.0f),
    vec3( 0.0f,  1.0f,  0.0f),
    vec3( 0.0f,  0.0f, -1.0f),
    vec3( 0.0f,  0.0f,  1.0f)
);

out vec3 f_fragPos;
out vec3 f_colour;
out vec3 f_normal;

void main(void)
{
    gl_Position = vp * model * vec4(coord3d, 1.0);
    f_colour = v_colour;
    f_normal = normals[v_normal_index];
    f_fragPos = vec3(model * vec4(coord3d, 1.0));
}
