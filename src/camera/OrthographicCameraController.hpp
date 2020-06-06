#pragma once

#include "CameraController.hpp"

class OrthographicCameraController : public CameraController
{
public:
    OrthographicCameraController(float aspect_ratio, float z_near = 0.1f, float z_far = 100.0f);
    void update(Input& input, const float timestep);

private:
    void moveForwards(const float& amount) override;
    void moveUpwards (const float& amount);
    void changeZoom  (const float& amount);
};