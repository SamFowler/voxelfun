#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera 
{
public:
    Camera();

    void init();
    void update();

    void setLookAt();

    void move(glm::vec3 magnitude);

    void updateDirection();
    void changePitch(float amount);
    void changeYaw(float amount);

    void moveForward(float amount);
    void moveSideways(float amount);
    void zoom(float amount);

    glm::mat4 getProjection();
    inline glm::mat4 getView() {return glm::lookAt(position, position + direction, up);}
    //inline glm::mat4 getView() {return glm::lookAt(position, look_at, up);}
    glm::mat4 getViewProjection();

private:
    glm::vec3 position;
    glm::vec3 look_at;
    glm::vec3 direction;
    glm::vec3 up;

    float yaw = -90.0f;
    float pitch;

    float aspect_ratio;
    unsigned int fov;
    float z_near;
    float z_far;

    bool is_ortho;

    glm::mat4 projection;
    glm::mat4 view;
};