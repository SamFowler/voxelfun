#pragma once
#include "Input.hpp"
#include "world/World.hpp"


class Game 
{
public:
    bool init();
    void shutdown();

    bool handleInput(Input& input);
    void tick(float timestep);

    void update(const float& timestep);
    void render();

private:
    bool m_is_running;

    World m_world;


    PerspectiveCameraController m_perspectiveCameraController = {45, (1280.0f/960.0f), 0.1f, 500.0f};
    //OrthographicCameraController m_ortho_camera_controller = {(1280.0f/960.0f)};
    //Camera m_camera;
    //Player m_player;
    //std::vector<Entities> m_entities;

};