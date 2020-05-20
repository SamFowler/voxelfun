#version 330 core
        
varying vec3 f_colour;

void main()
{
    gl_FragColor = vec4(f_colour.r, f_colour.g, f_colour.b, 1.0);
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}