#pragma once

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <memory>
#include <vector>

#include "sdl2_shared.cpp"
#include "Shader.hpp"
#include "VertexArrayObject.hpp"

class Renderer 
{

public:


    bool init(int win_width, int win_height);
    void draw();
    void destroy();
    void tempUpdate();
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

    VertexArrayObject my_cube;
    Shader m_shader; //TODO: will probably be a map of shaders eventually



};