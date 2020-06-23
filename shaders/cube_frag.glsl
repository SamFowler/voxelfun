#version 330 core
        
varying vec4 f_colour;
in vec3 f_normal;
in vec3 f_fragPos;
in vec2 f_tex_coord;

uniform vec3 lightPos;

uniform sampler2D our_texture;

void main()
{
    vec3 lightColour = vec3(1.0, 1.0, 1.0);

    float ambientStrength = 0.6;
    float diffuseStrength = 0.4;

    vec3 ambient = ambientStrength * lightColour;

    vec3 norm = (f_normal);
    vec3 lightDir = normalize(lightPos - f_fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour * diffuseStrength;

    vec4 colour = texture(our_texture, f_tex_coord);
    gl_FragColor = vec4( (ambient + diffuse) * colour.rgb, colour.a);

}