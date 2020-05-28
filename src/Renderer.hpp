#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include "sdl2_shared.cpp"

class Renderer 
{

public:

   // Renderer(int win_width, int win_height, int fov);
    bool init(int win_width, int win_height);

    void clear();
    void draw();

    void destroy();

private:
    std::shared_ptr<SDL_Window> m_window;
    SDL_GLContext m_context;
    
};