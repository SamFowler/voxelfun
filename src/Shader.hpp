#pragma once

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <string>

class Shader {

public:
    void Create(const std::string vertexShaderFile, std::string fragmentShaderFile);
    void Destroy();
    void Bind();

private:
    GLuint m_programId;

    GLuint CompileShader(const std::string shader, GLenum shaderType);
    GLuint LinkProgram(GLuint verterShaderID, GLuint fragmentShaderID);
    
    std::string LoadSource(const std::string& filepath);

};