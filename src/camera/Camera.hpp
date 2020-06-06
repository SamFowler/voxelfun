#pragma once

#include "../pch/pch_std.h"

class Camera
{
public:
    //OrthographicCamera(float left, float right, float bottom, float top);
    //PerspectiveCamera(float fov, float aspect_ratio, float z_near, float z_far);

    Camera();

    //virtual void setProjection() = 0;
    void setPerspectiveProjection(float fov, float aspect_ratio, float z_near, float z_far);
    void setOrthographicProjection(float left, float right, float bottom, float top, float z_near, float z_far);
    void setOrthographicProjection(float left, float right, float bottom, float top);

    const glm::vec3& getPosition()  const {return m_position;}
    const glm::vec3& getDirection() const {return m_direction;}

    void setPosition (const glm::vec3& position) {m_position = position; updateViewMatrix();}
    void setDirection(const glm::vec3& rotation);

    const glm::mat4& getProjectionMatrix()     const {return m_projection;}
    const glm::mat4& getViewMatrix()           const {return m_view;}
    const glm::mat4& getProjectionViewMatrix() const {return m_projection_view;}

private:
    void updateViewMatrix();
    void updateProjectionViewMatrix();

private:
    glm::mat4 m_projection;
    glm::mat4 m_view; 
    glm::mat4 m_projection_view;

    glm::vec3 m_position = { 0.0f, 2.0f, 0.0f };
    glm::vec3 m_direction = { 0.0f, -1.0f, 0.0f };
};
