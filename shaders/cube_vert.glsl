#version 330 core

layout (location = 0) in uint v_vertex_data;

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
out vec4 f_colour;
out vec3 f_normal;
out vec2 f_tex_coord;

void main(void)
{
    vec3 pos = vec3( 
            float((v_vertex_data & 0x3Fu) >> 0u),
            float((v_vertex_data & 0xFC0u) >> 6u),
            float((v_vertex_data & 0x3F000u) >> 12u)
                );
    gl_Position = vp * model * vec4(pos, 1.0);

    f_normal = normals[(v_vertex_data & 0xE0000000u) >> 29u];

    f_fragPos = vec3(model * vec4(pos, 1.0));

    f_tex_coord = vec2( 
                       ( (v_vertex_data & 0xFC0000u) >> 18u ) / 64.0f, 
                       ( (v_vertex_data & 0x1F000000u) >> 24u ) / 32.0f
                 );
}
