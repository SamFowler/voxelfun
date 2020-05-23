#pragma once
#include "Input.hpp"

class Game 
{
public:
    bool init();
    void shutdown();

    void handleInput();
    void tick(float timestep);

    bool update(Input& input);
    void render();

private:
    bool m_is_running;
};