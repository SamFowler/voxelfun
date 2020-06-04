#include "PerspectiveCamera.hpp"
//#include <iostream>

PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ratio, float z_near, float z_far) 
: m_projection(glm::perspective(fov, aspect_ratio, z_near, z_far)), m_view(1.0f)
{
    updateProjectionViewMatrix();
    std::cout << "fov:" << fov << ", ar: " << aspect_ratio << "zn:" << z_near << "zf:" << z_far << std::endl;
}

void PerspectiveCamera::setProjection(float fov, float aspect_ratio, float z_near, float z_far)
{
    m_projection = glm::perspective(fov, aspect_ratio, z_near, z_far);
    updateProjectionViewMatrix();
}

void PerspectiveCamera::setDirection(const glm::vec3& rotation)
{
    //rotation stores pitch,yaw,roll as x,y,z components

    m_direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    m_direction.y = sin(glm::radians(rotation.x));
    m_direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    m_direction = glm::normalize(m_direction);
    //std::cout << "setting direction: " << m_direction.x << "," << m_direction.y << "," << m_direction.z << std::endl;

    updateViewMatrix();
}

void PerspectiveCamera::updateViewMatrix()
{
    m_view = glm::lookAt(m_position, m_position + m_direction, glm::vec3(0.0, 1.0, 0.0));

	//m_view = glm::inverse(m_view);

    updateProjectionViewMatrix();
}

void PerspectiveCamera::updateProjectionViewMatrix()
{
    m_projection_view = m_projection * m_view;
}