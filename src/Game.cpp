#include "Game.hpp"
#include <iostream>

bool Game::Init() {
    m_isRunning = true;

    return true;
}

bool Game::Update(Input& input) {
    //std::cout << "Updating game" << std::endl;

    if (input.WasKeyPressed(SDLK_ESCAPE) || input.IsQuit()) {
        m_isRunning = false;
    }

    if (input.IsKeyHeld(SDLK_SPACE)) {
        std::cout << "Space bar helds" << std::endl;
    }

    if (input.WasButtonPressed(SDL_BUTTON_LEFT)) {
        pos2d mouse_pos = input.GetMousePos();
        std::cout << "Left mouse button pressed at position: " << mouse_pos.x << "," << mouse_pos.y << std::endl;
    }

    return m_isRunning;
}