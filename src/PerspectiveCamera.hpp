#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PerspectiveCamera 
{
public:
    PerspectiveCamera(float fov, float aspect_ratio, float z_near, float z_far);

    void setProjection(float fov, float aspect_ratio, float z_near, float z_far);

    void setPosition(const glm::vec3& position) {m_position = position; updateViewMatrix();};
    const glm::vec3& getPosition() const {return m_position;}

    void setDirection(const glm::vec3& rotation);
    const glm::vec3& getDirection() const {return m_direction;}    

    const glm::mat4& getProjection() const {return m_projection;};
    const glm::mat4& getView() const {return m_view;}
    const glm::mat4& getViewProjection() const {return m_projection_view;};

private:
    void updateViewMatrix();

    glm::mat4 m_projection;
    glm::mat4 m_view; 
    glm::mat4 m_projection_view;

    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_direction = { 0.0f, 1.0f, 0.0f };



};