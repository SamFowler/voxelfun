#pragma once

#include "pch/pch_std.h"

#include "Game.h"
#include "Renderer.h"
#include "Input.h"
#include "Timer.h"

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

    Timer m_timer;

    float last_ticks = 0.0f; //TODO move into timer/clock class

};
