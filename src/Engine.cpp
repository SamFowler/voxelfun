#include "Engine.hpp"
#include <iostream>

bool Engine::init()
{

    if( !m_renderer.init(1280, 960) )
        return false;
 
    if (!m_game.init())
        return false;

    if (!m_input.init())
        return false;

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
    }


    //engine clear up here
    m_renderer.destroy();
}

void Engine::frameSetup()
{
    
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


    m_game.update(m_input, timestep); //TODO input here temporary
    
    

    last_ticks = ticks;

}

void Engine::render()
{
    m_game.render();

    m_renderer.draw();
}
