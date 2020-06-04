#include "OrthographicCamera.hpp"

//#include <iostream>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_projection(glm::ortho(left, right, bottom, top, -1.0f, 100.0f)), m_view(1.0f)
{

    m_projection_view = m_projection * m_view;
}

void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
{

    m_projection = glm::ortho(left, right, bottom, top, -1.0f, 100.0f);
    updateProjectionViewMatrix();
}

void OrthographicCamera::setDirection(glm::vec3& rotation) 
{
    //std::cout << "setting dir to rot: " << rotation.x << "," << rotation.y << "," << rotation.z << std::endl;

    m_direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    m_direction.y = sin(glm::radians(rotation.x));
    m_direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    m_direction = glm::normalize(m_direction);
    //std::cout << "set direction: " << m_direction.x << "," << m_direction.y << "," << m_direction.z << std::endl;

    updateViewMatrix();
}  

void OrthographicCamera::updateViewMatrix()
{

    m_view = glm::lookAt(m_position,  m_position + m_direction, glm::vec3(0.0, 1.0, 0.0));

    /*
    std::cout << "updating view matrix with position: " << m_position.x << "," << m_position.y << "," << m_position.y << "," << m_position.z << std::endl;
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
    */
    //m_view = glm::inverse(transform);
    
    updateProjectionViewMatrix();
}

void OrthographicCamera::updateProjectionViewMatrix()
{
    m_projection_view = m_projection * m_view;
}