#include "Camera.h"


Camera::Camera()
{
    m_view = glm::mat4(1.0f);
}

/* OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
{
    m_projection = glm::ortho(left, right, bottom, top, -1.0f, 100.0f);
    m_view = glm::mat4(1.0f);
    updateProjectionViewMatrix();

}
PerspCamera::PerspCamera(float fov, float aspect_ratio, float z_near, float z_far) 
{
    m_projection = glm::perspective(fov, aspect_ratio, z_near, z_far);
    m_view = glm::mat4(1.0f);
    updateProjectionViewMatrix();
    std::cout << "fov:" << fov << ", ar: " << aspect_ratio << "zn:" << z_near << "zf:" << z_far << std::endl;
} */


void Camera::setOrthographicProjection(float left, float right, float bottom, float top, float z_near, float z_far)
{
    m_projection = glm::ortho(left, right, bottom, top, z_near, z_far);
    updateProjectionViewMatrix();
}
void Camera::setOrthographicProjection(float left, float right, float bottom, float top)
{
    m_projection = glm::ortho(left, right, bottom, top, -1.0f, 100.0f);
    updateProjectionViewMatrix();
}
void Camera::setPerspectiveProjection(float fov, float aspect_ratio, float z_near, float z_far)
{
    m_projection = glm::perspective(fov, aspect_ratio, z_near, z_far);
    updateProjectionViewMatrix();
}


void Camera::setDirection(const glm::vec3& rotation) 
{
    m_direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    m_direction.y = sin(glm::radians(rotation.x));
    m_direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    m_direction = glm::normalize(m_direction);

    updateViewMatrix();
}


void Camera::updateViewMatrix()
{
    m_view = glm::lookAt(m_position, m_position + m_direction, glm::vec3(0.0, 1.0, 0.0));

	//m_view = glm::inverse(m_view);

    updateProjectionViewMatrix();
}

void Camera::updateProjectionViewMatrix()
{
    m_projection_view = m_projection * m_view;
}