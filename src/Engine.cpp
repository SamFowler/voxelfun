#include "Engine.hpp"
#include <iostream>

bool Engine::Init() {
    
    if (!m_game.Init()) {
        return false;
    }

    if( !m_renderer.Init(680, 480) ) {
        return false;
    }

    m_isRunning = true;

    return true;

}

void Engine::Run() {
    std::cout << "Starting engine..." << std::endl;

    while (m_isRunning) {
        
        m_input.Collect();

        if (!m_game.Update(m_input)) {
            m_isRunning = false;
        }

        m_renderer.Draw();

    }

    //engine clear up here
    
    m_renderer.Destroy();
}