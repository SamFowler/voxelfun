#version 330 core

attribute vec3 coord3d;
attribute vec3 v_colour;
uniform mat4 mvp;
varying vec3 f_colour;

void main(void)
{
    gl_Position = mvp * vec4(coord3d, 1.0);
    f_colour = v_colour;
}
