#include "PerspectiveCameraController.hpp"

//#include <iostream>

#include "../pch/pch_std.h"

PerspectiveCameraController::PerspectiveCameraController(float fov, float aspect_ratio) 
: m_fov(fov), m_aspect_ratio(aspect_ratio), m_camera(m_fov, m_aspect_ratio, m_z_near, m_z_far)
{
    std::cout << "fov:" << m_fov << ", ar: " << m_aspect_ratio << "zn:" << m_z_near << "zf:" << m_z_far << std::endl;
}

PerspectiveCameraController::PerspectiveCameraController(float fov, float aspect_ratio, float z_near, float z_far) 
: m_fov(fov), m_aspect_ratio(aspect_ratio), m_z_near(z_near), m_z_far(z_far), m_camera(m_fov, m_aspect_ratio, m_z_near, m_z_far)
{
    std::cout << "fov:" << m_fov << ", ar: " << m_aspect_ratio << "zn:" << m_z_near << "zf:" << m_z_far << std::endl;
}

void PerspectiveCameraController::update(Input& input, const float timestep)
{

    float camera_move_speed = m_camera_speed + m_zoom;
    if (input.isKeyHeld(SDLK_w)) 
    {
        moveForwards(m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_s)) 
    {   
        moveForwards(-m_camera_speed * timestep);
    }
    if (input.isKeyHeld(SDLK_d)) 
    {   
        moveSideways(camera_move_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_a)) 
    {   
       moveSideways(-camera_move_speed * timestep);
    }

    if (input.isKeyHeld(SDLK_SPACE)) 
    {   
        moveUpwards(m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_LSHIFT)) 
    {   
        moveUpwards(-m_camera_speed * timestep);
    }

    if (input.isKeyHeld(SDLK_z)) 
    {   
        changeZoom(m_camera_zoom_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_x)) 
    {   
        changeZoom(-m_camera_zoom_speed * timestep);
    }


    //std::cout << "setting position: " << m_camera_position.x << "," << m_camera_position.y << "," << m_camera_position.z << std::endl;
    m_camera.setPosition(m_camera_position);


    glm::ivec2 rel_pos = input.getRelMousePos();
    //std::cout << "rel:" << rel_pos.x << "," << rel_pos.y << ", relmult: " << rel_pos.x * m_camera_rotation_speed<< "," << rel_pos.y * m_camera_rotation_speed<< std::endl;
    updatePitch(-rel_pos.y * m_camera_rotation_speed);
    updateYaw(rel_pos.x * m_camera_rotation_speed);
    
    //std::cout << std::endl;
    //std::cout << "setting direction: " << m_camera_rotation.x << "," << m_camera_rotation.y << "," << m_camera_rotation.z << std::endl;

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

void PerspectiveCameraController::moveUpwards(const float& amount)
{
    glm::vec3 side_direction = glm::normalize(glm::cross(m_camera.getDirection(), glm::vec3(0.0f, -1.0f, 0.0f)));
    glm::vec3 camera_up_direction = glm::normalize(glm::cross(m_camera.getDirection(), side_direction));
    m_camera_position += camera_up_direction * amount;
}

void PerspectiveCameraController::changeZoom(const float& amount)
{
    
    m_zoom += amount;
    if (m_zoom < -0.5f)
        m_zoom = -0.5f;
    else if (m_zoom > 0.5f) 
        m_zoom = 0.5f; 
    std::cout << "m_zoom: " << m_zoom << ", m_fov: " << m_fov << ", zoomed fov: " << m_fov + m_zoom << std::endl;

    m_camera.setProjection(m_fov + m_zoom, m_aspect_ratio, m_z_near, m_z_far);

}
