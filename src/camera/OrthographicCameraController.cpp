#include "OrthographicCameraController.hpp"

#include <iostream>

OrthographicCameraController::OrthographicCameraController(float aspect_ratio) 
: m_aspect_ratio(aspect_ratio), m_camera(-m_aspect_ratio * m_zoom, m_aspect_ratio * m_zoom, -m_zoom, m_zoom), m_camera_rotation({0.0f, 270.0f, 0.0f})
{
    std::cout << ", ar: " << m_aspect_ratio << "zn:" << m_z_near << "zf:" << m_z_far << std::endl;
}
/*
OrthographicCameraController::OrthographicCameraController(float aspect_ratio, float z_near, float z_far) 
:m_aspect_ratio(aspect_ratio), m_z_near(z_near), m_z_far(z_far), m_camera(-m_aspect_ratio, m_aspect_ratio, z_near, z_far), m_camera_rotation(0.0f)
{
    std::cout << ", ar: " << m_aspect_ratio << "zn:" << m_z_near << "zf:" << m_z_far << std::endl;
} 
*/

void OrthographicCameraController::update(Input& input, const float timestep)
{ 

    if (input.isKeyHeld(SDLK_s)) 
    {
        moveUpwards(-m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_w)) 
    {   
        moveUpwards(m_camera_speed * timestep);
    }
    if (input.isKeyHeld(SDLK_a)) 
    {   
        moveSideways(m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_d)) 
    {   
        moveSideways(-m_camera_speed * timestep);
    }

    if (input.isKeyHeld(SDLK_r)) 
    {   
        moveUpwards(m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_f)) 
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


    std::cout << "setting position: " << m_camera_position.x << "," << m_camera_position.y << "," << m_camera_position.z << std::endl;
    m_camera.setPosition(m_camera_position);


    glm::ivec2 rel_pos = input.getRelMousePos();
    updatePitch(-rel_pos.y * m_camera_rotation_speed);
    updateYaw(rel_pos.x * m_camera_rotation_speed);
    

    m_camera.setDirection(m_camera_rotation);
}



void OrthographicCameraController::updatePitch(const float& amount)
{
    m_camera_rotation.x += amount;

    if(m_camera_rotation.x > 89.0f)
        m_camera_rotation.x =  89.0f;
    else if(m_camera_rotation.x < -89.0f)
        m_camera_rotation.x = -89.0f;
}

void OrthographicCameraController::updateYaw(const float& amount)
{
    m_camera_rotation.y = glm::mod( m_camera_rotation.y + amount, 360.0f );
}

void OrthographicCameraController::moveForwards(const float& amount) 
{
    m_camera_position += m_camera.getDirection() * amount;
}

void OrthographicCameraController::moveSideways(const float& amount)
{
    m_camera_position += glm::normalize(glm::cross(m_camera.getDirection(), glm::vec3(0.0f, 1.0f, 0.0f))) * amount;
}

void OrthographicCameraController::moveUpwards(const float& amount)
{
    glm::vec3 side_direction = glm::normalize(glm::cross(m_camera.getDirection(), glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::vec3 camera_up_direction = glm::normalize(glm::cross(m_camera.getDirection(), side_direction));
    m_camera_position += camera_up_direction * amount;
}

void OrthographicCameraController::changeZoom(const float& amount)
{        
        m_zoom -= amount;
		m_zoom = std::max(m_zoom, 0.25f);
        m_zoom = std::min(m_zoom, 10.0f);
		m_camera.setProjection(-m_aspect_ratio * m_zoom, m_aspect_ratio * m_zoom, -m_zoom, m_zoom);
        std::cout << "zoom set to " << m_zoom << std::endl;

        m_camera_speed = m_zoom;
}

