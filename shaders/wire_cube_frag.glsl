#version 330 core
        
varying vec4 f_colour;
in vec3 f_fragPos;


void main()
{
    //gl_FragColor = vec4(f_colour.r, f_colour.g, f_colour.b, 1.0);
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    
    gl_FragColor = f_colour;
}