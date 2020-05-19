#include "PerspectiveCameraController.hpp"

#include <iostream>

PerspectiveCameraController::PerspectiveCameraController(float fov, float aspect_ratio) 
: m_fov(fov), m_aspect_ratio(aspect_ratio), m_camera(m_fov, m_aspect_ratio, m_z_near, m_z_far)
{
    std::cout << "fov:" << m_fov << ", ar: " << m_aspect_ratio << "zn:" << m_z_near << "zf:" << m_z_far << std::endl;
}

void PerspectiveCameraController::update(Input& input, const float timestep)
{ 
     
    if (input.isKeyHeld(SDLK_s)) 
    {
        moveForwards(m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_w)) 
    {   
        moveForwards(-m_camera_speed * timestep);
    }
    if (input.isKeyHeld(SDLK_a)) 
    {   
        moveSideways(m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_d)) 
    {   
       moveSideways(-m_camera_speed * timestep);
    }
    if (input.isKeyHeld(SDLK_f)) 
    {   
        //move_vec.z -= move_amount;
    }
    else if (input.isKeyHeld(SDLK_r)) 
    {   
        //move_vec.z += move_amount;
    }
    //std::cout << "setting position: " << m_camera_position.x << "," << m_camera_position.y << "," << m_camera_position.z << std::endl;
    m_camera.setPosition(m_camera_position);


    glm::ivec2 rel_pos = input.getRelMousePos();
    //std::cout << "rel:" << rel_pos.x << "," << rel_pos.y << ", relmult: " << rel_pos.x * m_camera_rotation_speed<< "," << rel_pos.y * m_camera_rotation_speed<< std::endl;
    updatePitch(-rel_pos.y * m_camera_rotation_speed);
    updateYaw(rel_pos.x * m_camera_rotation_speed);
    
    std::cout << std::endl;
    std::cout << "setting direction: " << m_camera_rotation.x << "," << m_camera_rotation.y << "," << m_camera_rotation.z << std::endl;

    m_camera.setDirection(m_camera_rotation);
}



void PerspectiveCameraController::updatePitch(const float& amount)
{
    m_camera_rotation.x += amount;

    if(m_camera_rotation.x > 89.0f)
        m_camera_rotation.x =  89.0f;
    else if(m_camera_rotation.x < -89.0f)
        m_camera_rotation.x = -89.0f;
}

void PerspectiveCameraController::updateYaw(const float& amount)
{
    m_camera_rotation.y = glm::mod( m_camera_rotation.y + amount, 360.0f );
}

void PerspectiveCameraController::moveForwards(const float& amount) 
{
    m_camera_position += m_camera.getDirection() * amount;
}

void PerspectiveCameraController::moveSideways(const float& amount)
{
    m_camera_position += glm::normalize(glm::cross(m_camera.getDirection(), glm::vec3(0.0f, 1.0f, 0.0f))) * amount;
}