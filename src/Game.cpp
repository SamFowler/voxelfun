#include "Game.h"
//#include <iostream>

#include "camera/OrthographicCameraController.h"
#include "camera/PerspectiveCameraController.h"

bool Game::init() 
{
    m_world.init();
    //m_camera.init();
    //m_player.init();
    //m_entities.init();

    m_camera_controller = std::make_unique<PerspectiveCameraController>(45, (1280.0f/960.0f), 0.1f, 500.0f);
    //m_camera_controller = std::make_unique<OrthographicCameraController>(1280.0f/960.0f);

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

void Game::update(Input& input, const float& timestep) 
{
    //m_perspectiveCameraController.update(input, timestep); // TODO: separate camera input handling and ticking
    //m_ortho_camera_controller.update(input, timestep);

    m_camera_controller->update(input, timestep);

    m_world.update(timestep);

    //m_camera.update(timestep);
    //m_player.update(timestep);
    //m_enetities.update(timestep);

}

void Game::render()
{
    //m_world.render(m_ortho_camera_controller.getCamera()); //m_perspectiveCameraController.GetCamera());
    m_world.render(m_camera_controller->getCamera()); //m_perspectiveCameraController.GetCamera());
    
    //m_camera.draw();
    //m_player.draw();
    //m_entities.draw();
}