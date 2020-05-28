#pragma once
#include "Input.hpp"
#include "world/World.hpp"


class Game 
{
public:
    bool init();
    void shutdown();

    void handleInput();
    void tick(float timestep);

    bool update(Input& input);

private:
    bool m_is_running;

    World m_world;
};