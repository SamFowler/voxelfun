#include "Renderer.hpp"
#include <iostream>


bool Renderer::Init(int win_width = 640, int win_height = 480) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL could not initialise. SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    m_window = sdl_shared(SDL_CreateWindow(
            "hello_sdl2",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            win_width, win_height,
            SDL_WINDOW_SHOWN |
            SDL_WINDOW_OPENGL
            ));

    if (m_window == nullptr) {
        std::cout << "Could not create window. SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    SDL_GL_CreateContext(m_window.get());

    std::cout << "Renderer successfully initialised with window width " << win_width << " and height " << win_height << std::endl; 
    return true;

}

void Renderer::Draw() {
    //std::cout << "Drawing game" << std::endl;

    glClearColor(0.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(m_window.get());
}