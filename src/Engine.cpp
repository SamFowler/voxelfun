#include "Engine.hpp"
#include <iostream>

Engine::Engine() 
{

}

Engine::~Engine()
{
}

bool Engine::init(int win_width = 640, int win_height = 480) 
{
    
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


    std::cout << "Initialising engine with heighst " << win_width << " and width " << win_height << std::endl; 

    m_isRunning = true; 
    
    std::cout << "Engine successfully initialised." << std::endl;
    return true;
}

void Engine::run() {
    std::cout << "Starting engine." << std::endl;
    std::cout << "running: " << m_isRunning << std::endl;

    while (m_isRunning) {
        
        pollWindowEvents();
        handleInput();
        update();
        render();

    }
}

void Engine::pollWindowEvents() {
    //std::cout << "Polling window events" << std::endl;
}

void Engine::handleInput() {
    //std::cout << "Handling input" << std::endl;
    while (SDL_PollEvent( &m_event ) != 0) {
        switch (m_event.type) {
            case SDL_QUIT:
                m_isRunning = false;
            case SDL_KEYDOWN:
                std::cout << "Key down: " << SDL_GetKeyName(m_event.key.keysym.sym) << std::endl;
            case SDL_KEYUP:
                std::cout << "Key up: " << SDL_GetKeyName(m_event.key.keysym.sym) << std::endl;
        }
    }
}

void Engine::update() {
   //std::cout << "Updating" << std::endl;

}

void Engine::render() {
    //std::cout << "Rendering" << std::endl;

    glClearColor(0.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(m_window.get());

}


