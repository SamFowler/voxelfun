#include "Game.hpp"
#include <iostream>

bool Game::Init() {
    m_isRunning = true;

    return true;
}

bool Game::Update(Input& input) {
    //std::cout << "Updating game" << std::endl;


    if (input.wasKeyPressed(SDLK_ESCAPE) || input.isQuit()) {
        m_isRunning = false;
    }

    if (input.isKeyHeld(SDLK_SPACE)) {
        std::cout << "Space bar held" << std::endl;
    }



    return m_isRunning;
}