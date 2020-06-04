#include "Engine.hpp"


//#include <iostream>
//#include <chrono>


bool Engine::init()
{

    if( !m_renderer.init(1280, 960) )
        return false;
 
    if (!m_game.init())
        return false;

    if (!m_input.init())
        return false;

    m_timer.init();

    m_is_running = true;

    return true;
}

void Engine::run() 
{
    std::cout << "Starting engine..." << std::endl;

    while (m_is_running) 
    {
        frameSetup();
        update();
        render();
        m_timer.printFPS();
    }


    //engine clear up here
    m_renderer.destroy();
}

void Engine::frameSetup()
{
    m_timer.frameStart();

    m_input.collect();
    m_renderer.clear();

    if(!m_game.handleInput(m_input))
    {
        m_is_running = false;
    }
}

void Engine::update()
{
    float ticks = (SDL_GetTicks() / 1000.0);
    float timestep = (last_ticks - ticks);

    while (m_timer.checkDeltaTimeReached())
    {
        m_game.update(m_input, m_timer.getDeltaTime()); //TODO input here temporary
       m_timer.endUpdateLoop();
    }


    last_ticks = ticks;

}

void Engine::render()
{
    m_timer.frameEnd();

    m_game.render();

    m_renderer.draw();
}
