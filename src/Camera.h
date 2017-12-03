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
    bool isUoToDate = false;
    glm::mat4 matrix;
};