#include "Shader.hpp"
#include <fstream>
#include <iostream>


namespace {
    struct ShaderReader
    {
        ShaderReader(std::string path);
        std::string source;
    };

    ShaderReader::ShaderReader(std::string path) 
    {   
        std::ifstream inFile(path);
        std::string line;
        std::cout << "Reading file: " << path << std::endl;
        if (inFile.is_open())
        {
            while (std::getline(inFile, line))
            {   
                source = source + line + "\n";
            }
            inFile.close();
        }
        else
        {
            std::cout << "Could not open file " << path << std::endl;
        }
    }
}


void Shader::Create(const std::string vertexShaderFile, const std::string fragmentShaderFile) 
{
    glUseProgram(0);

    const std::string vertexShaderPath("shaders/" + vertexShaderFile + "_vert.glsl");
    const std::string fragmentShaderPath("shaders/" + fragmentShaderFile + "_frag.glsl");


    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShaderPath);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

    m_programId = LinkProgram(vs, fs);

    /*
    unsigned int programId = glCreateProgram();
    glAttachShader(programId, vs);
    glAttachShader(programId, fs);
    glLinkProgram(programId);
    glValidateProgram(programId);

    glDeleteShader(vs);
    glDeleteShader(fs);
    */

    //return programId;

    //compile vertex shader
    //compile fragment shader
    // link shaders to program (getting m_programId)
        //m_programId = LinkProgram(vertexShaderId, fragmentShaderId);
    //check for compile / link errors
}

void Shader::Destroy() 
{
    glDeleteProgram(m_programId);
    m_programId = 0;
}

void Shader::Use() 
{
    glUseProgram(m_programId);
}

GLuint Shader::CompileShader(GLuint shaderType, const std::string& shaderSourcePath) 
{
    unsigned int id = glCreateShader(shaderType);

    ShaderReader reader = ShaderReader(shaderSourcePath);
    const GLchar* const shaderSourcePtr = reader.source.c_str();
    //const GLint shaderSourceLength = source.length();

    glShaderSource(id, 1, &shaderSourcePtr, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) 
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length* sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << std::endl << message << std::endl;
        glDeleteShader(id);
        return 0;
    } else {
        std::cout << (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader compiled successfully" << std::endl;
    }

    return id;
}


GLuint Shader::LinkProgram(GLuint verterShaderId, GLuint fragmentShaderId) 
{
    //TODO: add GL error checking


    unsigned int programId = glCreateProgram();

    glAttachShader(programId, verterShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);
    glValidateProgram(programId);

    //TODO: error checking on shader linking

    //TODO: check whether to DeleteShader or DetachShader
    glDeleteShader(verterShaderId);
    glDeleteShader(fragmentShaderId);

    /*
    auto id = glCreateProgram();

    glAttachShader(id, verterShaderID);
    glAttachShader(id, fragmentShaderID);

    glLinkProgram(id);

    glDetachShader(id, fragmentShaderID);
    glDetachShader(id, verterShaderID);
    */

    return programId;
}

