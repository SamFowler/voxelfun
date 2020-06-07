#include "CameraController.h"

void CameraController::updatePitch(const float& amount)
{
    m_camera_rotation.x += amount;

    if(m_camera_rotation.x > 89.0f) 
        m_camera_rotation.x =  89.0f;
    else if(m_camera_rotation.x < -89.0f)
        m_camera_rotation.x = -89.0f;
}

void CameraController::updateYaw(const float& amount)
{
    m_camera_rotation.y = glm::mod( m_camera_rotation.y + amount, 360.0f );
}

void CameraController::moveForwards(const float& amount) 
{
    m_camera_position += m_camera.getDirection() * amount;
}

void CameraController::moveSideways(const float& amount)
{
    m_camera_position += glm::normalize(glm::cross(m_camera.getDirection(), glm::vec3(0.0f, 1.0f, 0.0f))) * amount;
}

void CameraController::moveUpwards(const float& amount)
{
    glm::vec3 side_direction = glm::normalize(glm::cross(m_camera.getDirection(), glm::vec3(0.0f, -1.0f, 0.0f)));
    glm::vec3 camera_up_direction = glm::normalize(glm::cross(m_camera.getDirection(), side_direction));
    m_camera_position += camera_up_direction * amount;
}

void CameraController::printCamera() 
{
    std::cout << std::setprecision(3) << 
                           "[camera]: pos[" << m_camera_position.x << "," << m_camera_position.y << ","  << m_camera_position.z << "], "
                           "rot[" << m_camera_rotation.x << "," << m_camera_rotation.y << ","  << m_camera_rotation.z << "]" << std::endl;

};



























