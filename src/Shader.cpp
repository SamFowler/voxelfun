#include "Shader.hpp"
#include <fstream>
#include <iostream>

void Shader::Create(const std::string vertexShaderFile, std::string fragmentShaderFile) 
{
    glUseProgram(0);

    const std::string vertFilepath("shaders/" + vertexShaderFile + "_vert.glsl");
    const std::string fragFilepath("shaders/" + fragmentShaderFile + "_frag.glsl");

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

void Shader::Bind() 
{
    glUseProgram(m_programId);
}

GLuint CompileShader(const std::string shader, GLenum shaderType) 
{
    return 0; //TEMP RETURN
}
GLuint LinkProgram(GLuint verterShaderID, GLuint fragmentShaderID) 
{
    //TODO: add GL error checking

    auto id = glCreateProgram();

    glAttachShader(id, verterShaderID);
    glAttachShader(id, fragmentShaderID);

    glLinkProgram(id);

    glDetachShader(id, fragmentShaderID);
    glDetachShader(id, verterShaderID);

    return id;
}

std::string Shader::LoadSource(const std::string& filepath) 
{
    std::ifstream file(filepath.data(), std::ios::in | std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        std::cout << "Could not open file " << filepath << std::endl;
        return "";
    }

    std::string fileContents(file.tellg(), 0);
    file.seekg(0, file.beg);
    file.read(fileContents.data(), fileContents.size());
    return fileContents;
}