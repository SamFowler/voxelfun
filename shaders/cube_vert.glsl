#version 330 core

layout (location = 0) in uvec3 coord3d;
layout (location = 1) in vec3 v_colour;
layout (location = 2) in vec3 v_normal;

uniform mat4 model;
uniform mat4 vp;
uniform mat4 normal_matrix;

out vec3 f_fragPos;
out vec3 f_colour;
out vec3 f_normal;

void main(void)
{
    gl_Position = vp * model * vec4(coord3d, 1.0);
    f_colour = v_colour;
    f_normal = v_normal;
    f_fragPos = vec3(model * vec4(coord3d, 1.0));
}
