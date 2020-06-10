#include "OrthographicCameraController.h"

OrthographicCameraController::OrthographicCameraController(float aspect_ratio, float z_near, float z_far) 
{
    m_camera_speed = 5.0f;
    m_camera_rotation_speed = 2.0f;
    m_camera_zoom_speed = 5.0f;

    m_aspect_ratio = aspect_ratio;
    m_z_near = z_near; 
    m_z_far = z_far;



    m_camera.setOrthographicProjection(-m_aspect_ratio * m_zoom, m_aspect_ratio * m_zoom, -m_zoom, m_zoom, m_z_near, m_z_far); 

}

OrthographicCameraController::OrthographicCameraController(float aspect_ratio, float z_near, float z_far, const glm::vec3& camera_pos, const glm::vec3& camera_rot) 
{
    m_camera_speed = 25.0f;
    m_camera_rotation_speed = 2.0f;
    m_camera_zoom_speed = 10.0f;

    m_camera_position = camera_pos;
    m_camera_rotation = camera_rot;

    m_zoom = 4.0f;

    m_aspect_ratio = aspect_ratio;
    m_z_near = z_near; 
    m_z_far = z_far;

    m_camera.setOrthographicProjection(-m_aspect_ratio * m_zoom, m_aspect_ratio * m_zoom, -m_zoom, m_zoom, m_z_near, m_z_far); 

}

void OrthographicCameraController::update(Input& input, const float timestep)
{ 

    if (input.isKeyHeld(SDLK_s)) 
    {
        moveForwards(-m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_w)) 
    {   
        moveForwards(m_camera_speed * timestep);
    }
    if (input.isKeyHeld(SDLK_a)) 
    {   
        moveSideways(-m_camera_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_d)) 
    {   
        moveSideways(m_camera_speed * timestep);
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

    if (input.wasKeyPressed(SDLK_UP)) 
    {   
        std::cout << m_camera_rotation.x << std::endl;
        m_camera_rotation.x -= 2.5;
        m_camera_rotation.x += std::fmod(m_camera_rotation.x, 5);
        updatePitch(-m_camera_rotation_speed * timestep);
    }
    else if (input.wasKeyPressed(SDLK_DOWN)) 
    {   
        std::cout << m_camera_rotation.x << std::endl;
        m_camera_rotation.x += 2.5;
        m_camera_rotation.x -= std::fmod(m_camera_rotation.x, 5);

        updatePitch(m_camera_rotation_speed * timestep);
    }

    if (input.isKeyHeld(SDLK_LEFT)) 
    {   
        updateYaw(-m_camera_rotation_speed * timestep);
    }
    else if (input.isKeyHeld(SDLK_RIGHT)) 
    {   
        updateYaw(m_camera_rotation_speed * timestep);
    }


    m_camera.setPosition(m_camera_position);

    glm::ivec2 rel_pos = input.getRelMousePos();
    updatePitch(-rel_pos.y * m_camera_rotation_speed * timestep);
    updateYaw(rel_pos.x * m_camera_rotation_speed * timestep);
    
    m_camera.setDirection(m_camera_rotation);
 
    //printCamera();
} 

void OrthographicCameraController::moveForwards(const float& amount) 
{
    //m_camera_position += m_camera.getDirection() * amount;
    //m_camera_position += glm::normalize(glm::cross(m_camera.getDirection(), glm::vec3(0.0f, 1.0f, 0.0f))) * amount;
    std::cout << "ortho forwards" <<std::endl;
    m_camera_position += glm::normalize(glm::vec3(m_camera.getDirection().x, 0.0f, m_camera.getDirection().z)) * amount;
}


void OrthographicCameraController::moveUpwards(const float& amount)
{
    //glm::vec3 side_direction = glm::normalize(glm::cross(m_camera.getDirection(), glm::vec3(0.0f, -1.0f, 0.0f)));
    glm::vec3 camera_up_direction = {0.0f, 1.0f, 0.0f};//glm::normalize(glm::cross(m_camera.getDirection(), side_direction));
    m_camera_position += camera_up_direction * amount;
}

void OrthographicCameraController::changeZoom(const float& amount)
{        
        m_zoom -= amount; 
		m_zoom = std::max(m_zoom, 0.05f);
        m_zoom = std::min(m_zoom, 50.0f);

        m_camera.setOrthographicProjection(-m_aspect_ratio * m_zoom, m_aspect_ratio * m_zoom, -m_zoom, m_zoom, m_z_near, m_z_far);
        std::cout << "zoom set to " << m_zoom << std::endl;

        //m_camera_speed = m_zoom;
}