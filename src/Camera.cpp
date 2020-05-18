#include "Camera.hpp"
#include <iostream>

Camera::Camera() 
{

}

void Camera::init() 
{

position = (glm::vec3(0.0, 2.0, 0.0));
look_at = (glm::vec3(0.0, 0.0, -4.0));
direction = (glm::vec3(1.0, -1.0, -1.0));
up = (glm::vec3(0.0, 1.0, 0.0));
}

void Camera::update()
{
    look_at = position + direction;
}

void Camera::move(glm::vec3 magnitude)
{
    position = position + magnitude;
}

void Camera::updateDirection()
{
    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    direction = glm::normalize(dir);
    std::cout << "yaw: " << yaw << ", pitch: "<< pitch << ", dir: " << direction.x << "," << direction.y << "," << direction.z << std::endl;
}

void Camera::changePitch(float amount)
{
    pitch -= amount;

    if(pitch > 89.0f)
    {
        pitch =  89.0f;
    }
    if(pitch < -89.0f)
    {
        pitch = -89.0f;
    }
}

void Camera::changeYaw(float amount)
{
    yaw = glm::mod( yaw + amount, 360.0f );
}


void Camera::moveForward(float amount) 
{
    position += direction * amount;
}

void Camera::moveSideways(float amount)
{
    position += glm::normalize(glm::cross(direction, up)) * amount;
}

void Camera::zoom(float amount)
{
    //position += glm::normalize()
}