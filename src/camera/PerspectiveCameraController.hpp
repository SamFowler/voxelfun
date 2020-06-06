#pragma once

#include "CameraController.hpp"

class PerspectiveCameraController : public CameraController
{
public:
    //PerspController(float fov, float aspect_ratio);
    PerspectiveCameraController(float fov, float aspect_ratio, float z_near = 0.1f, float z_far = 100.0f) ;
    
    void update(Input& input, const float timestep);

private:
    void changeZoom(const float& amount);
    
    float m_fov;

};