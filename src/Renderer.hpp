#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
//#include <GL/gl.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <memory>
#include "sdl2_shared.cpp"
#include "Shader.hpp"

class Renderer {

public:
    bool Init(int win_width, int win_height);
    void Draw();
    void Destroy();
    void TempUpdate();
private:
    std::shared_ptr<SDL_Window> m_window;
    SDL_GLContext m_context;


    //temp variables for first shader draw
    GLuint m_buffer;
    GLuint m_vbo_cube_vertices;
    GLuint m_vbo_cube_colours;
    GLuint m_ibo_cube_elements;

    GLint attribute_coord3d, attribute_v_colour;
    GLint uniform_mvp;

    float m_positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f,
    };

    float m_squ_positions[8] = {
        -0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f,
    };

    float m_cube_vertices[24] = {
        //front
        -0.5f, -0.5f, 0.5f,
         0.5f, -0.5f, 0.5f,
         0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,

        //back
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    float m_cube_colours[24] = {
        //front colours
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        //back colours
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
    };

    GLushort m_cube_elements[36] = {
        //front
        0, 1, 2,
        2, 3, 0,
        //right
        1, 5, 6,
        6, 2, 1,
        //back 
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        //bottom
        4, 5, 1,
        1, 0, 4,
        //top
        3, 2, 6,
        6, 7, 3,
    };

    Shader m_shader; //TODO: will probably be a map of shaders eventually



};