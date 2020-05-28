#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "sdl2_shared.cpp"

#include "Game.hpp"
#include "Renderer.hpp"
#include "Input.hpp"

class Engine 
{

public:

    bool init();
    void run();
    
    void frameSetup();
    void update();
    void render();

    Game m_game;
    Renderer m_renderer;
    Input m_input;
    //Events m_events;

private:
    bool m_is_running;

};
