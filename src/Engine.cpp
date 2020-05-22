#include "Engine.hpp"
#include <iostream>

bool Engine::init()
{
    
    if (!m_game.init())
    {
        return false;
    }

    if( !m_renderer.init(1280, 960) )
    {
        return false;
    }

    if (!m_input.init())
    {
        return false;
    }

    m_is_running = true;

    return true;
}

void Engine::run() 
{
    std::cout << "Starting engine..." << std::endl;

    while (m_is_running) 
    {
        m_input.collect();

        if (!m_game.update(m_input)) 
        {
            m_is_running = false;
        }
        m_renderer.tempUpdate(m_input);
        m_renderer.draw();
    }

    //engine clear up here
    
    m_renderer.destroy();
}