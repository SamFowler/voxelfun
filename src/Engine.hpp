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
    Game m_game;
    Renderer m_renderer;
    Input m_input;

private:
    bool m_is_running;

};
