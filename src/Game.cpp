#include "Game.hpp"
#include <iostream>

bool Game::init() 
{
    m_world.init();
    //m_camera.init();
    //m_player.init();
    //m_entities.init();

    m_is_running = true;
    return m_is_running;
}

bool Game::handleInput(Input& input)
{

    if (input.wasKeyPressed(SDLK_ESCAPE) || input.isQuit())
    {
        m_is_running = false;
    }
    
    if (input.wasButtonPressed(SDL_BUTTON_LEFT))
    {
        glm::ivec2 mouse_pos = input.getMousePos();
        std::cout << "Left mouse button pressed at position: " << mouse_pos.x << "," << mouse_pos.y << std::endl;
    } 

    return m_is_running;

}

void Game::update(const float& timestep) 
{
    m_world.update(timestep);
    //m_camera.update(timestep);
    //m_player.update(timestep);
    //m_enetities.update(timestep);

}

void Game::render()
{
    m_world.render();
    //m_camera.draw();
    //m_player.draw();
    //m_entities.draw();
}