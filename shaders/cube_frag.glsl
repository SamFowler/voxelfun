#version 330 core
        
varying vec3 f_colour;
in vec3 f_normal;
in vec3 f_fragPos;

uniform vec3 lightPos;

void main()
{
    //gl_FragColor = vec4(f_colour.r, f_colour.g, f_colour.b, 1.0);
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    
    vec3 lightColour = vec3(1.0, 1.0, 1.0);



    float ambientStrength = 0.6;
    float diffuseStrength = 0.4;

    vec3 ambient = ambientStrength * lightColour;

    vec3 norm = normalize(f_normal);
    vec3 lightDir = normalize(lightPos - f_fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour * diffuseStrength;

    vec3 result = (ambient + diffuse) * vec3(f_colour.r, f_colour.g, f_colour.b);
    gl_FragColor = vec4(result, 1.0);
}