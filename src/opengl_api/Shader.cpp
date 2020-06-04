#include "Shader.hpp"
//#include <fstream>
//#include <iostream>

 
namespace 
{
    struct ShaderReader
    {
        ShaderReader(std::string path);
        std::string source;
    };

    ShaderReader::ShaderReader(std::string path) 
    {   
        std::ifstream in_file(path);
        std::string line;
        std::cout << "Reading file: " << path << std::endl;
        if (in_file.is_open())
        {
            while (std::getline(in_file, line))
            {   
                source = source + line + "\n";
            }
            in_file.close();
        }
        else
        {
            std::cout << "Could not open file " << path << std::endl;
        }
    }
} //namespace


void Shader::create(const std::string vertex_shader_file, const std::string fragment_shader_file) 
{
    glUseProgram(0);

    const std::string vertex_shader_path("shaders/" + vertex_shader_file + "_vert.glsl");
    const std::string fragment_shader_path("shaders/" + fragment_shader_file + "_frag.glsl");


    GLuint vs = compileShader(GL_VERTEX_SHADER, vertex_shader_path);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader_path);

    m_program_id = linkProgram(vs, fs);
}

void Shader::destroy() 
{
    glDeleteProgram(m_program_id);
    m_program_id = 0;
}

void Shader::use() 
{
    glUseProgram(m_program_id);
}

GLint Shader::getAttributeLocation(const char* name)
{
    GLint attribute_location = glGetAttribLocation(m_program_id, name);
    if (attribute_location == -1) 
    {
        std::cout << "Could not bind attribute: " << name << std::endl;
    }
    return attribute_location;
}

GLint Shader::getUniformLocation(const char* name) 
{
    GLint uniform_location = glGetUniformLocation(m_program_id, name);
    if (uniform_location == -1) 
    {
        std::cout << "Could not bind uniform: " << name << std::endl;
    }
    return uniform_location;
}


GLuint Shader::compileShader(GLuint shader_type, const std::string& shader_source_path) 
{
    unsigned int id = glCreateShader(shader_type);

    ShaderReader reader = ShaderReader(shader_source_path);
    const GLchar* const shader_source_ptr = reader.source.c_str();
    //const GLint shaderSourceLength = source.length();

    glShaderSource(id, 1, &shader_source_ptr, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) 
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length* sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << std::endl << message << std::endl;
        glDeleteShader(id);
        return 0;
    } 
    else 
    {
        std::cout << (shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader compiled successfully" << std::endl;
    }

    return id;
}


GLuint Shader::linkProgram(GLuint verter_shader_id, GLuint fragment_shader_id) 
{
    //TODO: add GL error checking


    unsigned int programId = glCreateProgram();

    glAttachShader(programId, verter_shader_id);
    glAttachShader(programId, fragment_shader_id);

    glLinkProgram(programId);
    glValidateProgram(programId);

    //TODO: error checking on shader linking

    //TODO: check whether to DeleteShader or DetachShader
    glDeleteShader(verter_shader_id);
    glDeleteShader(fragment_shader_id);

    return programId;
}

