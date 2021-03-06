#pragma once

#include "../pch/pch_std.h"

class Shader 
{

public:
    void create(const std::string vertex_shader_file, std::string fragment_shader_file);
    void destroy();
    void use();

    GLint getAttributeLocation(const char* name);
    GLint getUniformLocation(const char* name);

private:
    GLuint m_program_id;

    GLuint compileShader(GLuint shader_type, const std::string& shader_source_path) ;
    GLuint linkProgram(GLuint verter_shader_id, GLuint fragment_shader_id);
    
};