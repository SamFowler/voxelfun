#pragma once

#include "../pch/pch_std.h"

#include "Camera.h"
#include "../Input.h"


class CameraController
{
public:
    virtual ~CameraController() = default;
    virtual void update(Input& input, const float timestep) = 0;

    Camera getCamera() {return m_camera;}

    void printCamera();

protected:

    void updateYaw(const float& amount);
    void updatePitch(const float& amount);

    virtual void moveForwards(const float& amount);
    void moveSideways(const float& amount);
    void moveUpwards(const float& amount);
    virtual void changeZoom(const float& amount) = 0;

    Camera m_camera;

    float m_aspect_ratio;

    float m_z_near = 1.0f;
    float m_z_far = 100.0f;
    float m_zoom = 2.0f;

    glm::vec3 m_camera_position = {0.5f, 3.0f, 0.0f};
    glm::vec3 m_camera_rotation = {-20.0f, 45.0f, 0.0f}; //pitch,yaw,roll (degrees)

    float m_camera_speed = 5.0f;
    float m_camera_rotation_speed = 0.15f;
    float m_camera_zoom_speed = 1.0f;
};
