#pragma once
#include "OrthographicCamera.hpp"
#include "../Input.hpp"

class OrthographicCameraController 
{
public:
    OrthographicCameraController(float aspectRatio);
    //OrthographicCameraController(float aspectRatio, float z_near, float z_far);

    void update(Input& input, const float timestep);

    OrthographicCamera& getCamera() { return m_camera; }
	//const OrthographicCamera& GetCamera() const { return m_camera; }

private:

    void updateYaw(const float& amount);
    void updatePitch(const float& amount);

    void moveForwards(const float& amount);
    void moveSideways(const float& amount);
    void moveUpwards(const float& amount);
    void changeZoom(const float& amount);

    float m_aspect_ratio;

    float m_z_near = 1.0f;
    float m_z_far = 100.0f;
    float m_zoom = 2.0f;

    OrthographicCamera m_camera;

    glm::vec3 m_camera_position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_camera_rotation = {0.0f, -90.0f, 0.0f}; //pitch,yaw,roll (degrees)

    float m_camera_speed = 5.0f;
    float m_camera_rotation_speed = 0.15f;
    float m_camera_zoom_speed = 1.0f;

};