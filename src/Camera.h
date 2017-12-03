#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
    Camera();
    ~Camera();

    void Move(glm::vec3 move);
    void Translate(glm::vec3 tranlation);

    float* getDataPtr();

private:
    glm::mat4 getRotation();
    void update();

    bool isUpToDate = false;
    glm::vec4 pos;
    float yaw;
    float pitch;
    glm::mat4 matrix;
};