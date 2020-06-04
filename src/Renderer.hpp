#pragma once

#include "pch/pch_std.h"

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