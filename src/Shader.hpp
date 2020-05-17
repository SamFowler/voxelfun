#pragma once

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <string>

class Shader {

public:
    //void Create(const std::string vertexShaderFile, std::string fragmentShaderFile);
    void Create(const std::string vertexShaderFile, std::string fragmentShaderFile);
    void Destroy();
    void Use();

private:
    GLuint m_programId;

    GLuint CompileShader(GLuint shaderType, const std::string& shaderSourcePath) ;
    GLuint LinkProgram(GLuint verterShaderID, GLuint fragmentShaderID);
    
};