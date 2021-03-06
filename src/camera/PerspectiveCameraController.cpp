#include "PerspectiveCameraController.h"

PerspectiveCameraController::PerspectiveCameraController(float fov, float aspect_ratio, float z_near, float z_far) 
: m_fov(fov)
{
    m_aspect_ratio = aspect_ratio;
    m_z_near = z_near;
    m_z_far = z_far;

    m_camera_speed = 25.0f;

    m_fov = fov;

    m_camera.setPerspectiveProjection(m_fov, m_aspect_ratio, m_z_near, m_z_far);
}

PerspectiveCameraController::PerspectiveCameraController(float fov, float aspect_ratio, float z_near, float z_far, const glm::vec3& camera_pos, const glm::vec3& camera_rot) 
: m_fov(fov)
{
    m_aspect_ratio = aspect_ratio;
    m_z_near = z_near;
    m_z_far = z_far;

    m_camera_position = camera_pos;
    m_camera_rotation = camera_rot;

    m_camera_speed = 25.0f;

    m_fov = fov;

    m_camera.setPerspectiveProjection(m_fov, m_aspect_ratio, m_z_near, m_z_far);
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

    m_camera.setPosition(m_camera_position);

    glm::ivec2 rel_pos = input.getRelMousePos();
    updatePitch(-rel_pos.y * m_camera_rotation_speed);
    updateYaw(rel_pos.x * m_camera_rotation_speed);
    
    m_camera.setDirection(m_camera_rotation);

    //printCamera();
}

void PerspectiveCameraController::changeZoom(const float& amount)
{
    
    m_zoom += amount;
    if (m_zoom < -0.5f)
        m_zoom = -0.5f;
    else if (m_zoom > 0.5f) 
        m_zoom = 0.5f; 
    std::cout << "m_zoom: " << m_zoom << ", m_fov: " << m_fov << ", zoomed fov: " << m_fov + m_zoom << std::endl;

    m_camera.setPerspectiveProjection(m_fov + m_zoom, m_aspect_ratio, m_z_near, m_z_far);
}