#include "Game.hpp"
#include <iostream>

bool Game::init() 
{
    m_is_running = true;
    return true;
}

bool Game::update(Input& input) 
{

    if (input.wasKeyPressed(SDLK_ESCAPE) || input.isQuit())
    {
        m_is_running = false;
    }

    /*
    if (input.isKeyHeld(SDLK_SPACE))
    {
        std::cout << "Space bar helds" << std::endl;
    }
    */
    
    if (input.wasButtonPressed(SDL_BUTTON_LEFT))
    {
        glm::ivec2 mouse_pos = input.getMousePos();
        std::cout << "Left mouse button pressed at position: " << mouse_pos.x << "," << mouse_pos.y << std::endl;
    } 
    

    return m_is_running;
}