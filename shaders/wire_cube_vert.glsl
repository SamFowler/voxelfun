#version 330 core

layout (location = 0) in uvec3 coord3d;
layout (location = 1) in vec4 v_colour;

uniform mat4 model;
uniform mat4 vp;

//out vec3 f_fragPos;
out vec4 f_colour;

void main(void)
{
    gl_Position = vp * model * vec4(coord3d, 1.0);
    f_colour = v_colour;
    //f_fragPos = vec3(model * vec4(coord3d, 1.0));
}
