#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "sdl2_shared.cpp"

#include "Game.hpp"
#include "Renderer.hpp"
#include "Input.hpp"

class Engine {

public:

    bool Init();
    void Run();
    Game m_game;
    Renderer m_renderer;
    Input m_input;

private:
    //void handleInput();
    //void update();
    //void render();

    bool m_isRunning;

};
