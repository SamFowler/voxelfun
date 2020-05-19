#pragma once

#include "PerspectiveCamera.hpp"

#include "Input.hpp"

class PerspectiveCameraController 
{
public:
    PerspectiveCameraController(float fov, float aspect_ratio);

    void update(Input& input, const float timestep);

    PerspectiveCamera& GetCamera() { return m_camera; }
	//const PerspectiveCamera& GetCamera() const { return m_camera; }

private:

    void updateYaw(const float& amount);
    void updatePitch(const float& amount);

    void moveForwards(const float& amount);
    void moveSideways(const float& amount);

    int m_fov;
    float m_aspect_ratio;

    float m_z_near = 1.0f;
    float m_z_far = 100.0f;
    float m_zoom = 0.1f;

    PerspectiveCamera m_camera;

    glm::vec3 m_camera_position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_camera_rotation = {0.0f, -90.0f, 0.0f}; //pitch,yaw,roll (degrees)

    float m_camera_speed = 5.0f;
    float m_camera_rotation_speed = 0.15f;

};