#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
//#include <GL/gl.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <memory>
#include "sdl2_shared.cpp"


class Renderer {

public:
    bool Init(int win_width, int win_height);
    void Draw();

private:
    std::shared_ptr<SDL_Window> m_window;
    //SDL_GLContext m_context;

    //temp variables for first shader draw
    float m_positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f,
    };
    unsigned int m_buffer;

};