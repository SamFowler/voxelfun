#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "sdl2_shared.cpp"
#include <GL/glew.h>
#include <GL/gl.h>

class Engine {

public:
    Engine();
    ~Engine();

    bool init(int width, int height);

    void run();


private:
    void pollWindowEvents();
    void handleInput();
    void update();
    void render();

    bool m_isRunning;
    SDL_Event m_event;
    std::shared_ptr<SDL_Window> m_window;

};
