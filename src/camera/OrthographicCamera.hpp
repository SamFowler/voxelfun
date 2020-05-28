#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrthographicCamera
{
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void setProjection(float left, float right, float bottom, float top);

    const glm::vec3& getPosition() const { return m_position; }
    void setPosition(const glm::vec3& position) { m_position = position; updateViewMatrix(); }

    const glm::vec3& getDirection() const { return m_direction; }
    void setDirection(glm::vec3& rotation);

    const glm::mat4& getProjectionMatrix() const { return m_projection; }
    const glm::mat4& getViewMatrix() const { return m_view; }
    const glm::mat4& getProjectionViewMatrix() const { return m_projection_view; }

private:

    void updateViewMatrix();
    void updateProjectionViewMatrix();

    glm::mat4 m_projection;
    glm::mat4 m_view; 
    glm::mat4 m_projection_view;

    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };;
    glm::vec3 m_direction = { 0.0f, -1.0f, 0.0f };;
};