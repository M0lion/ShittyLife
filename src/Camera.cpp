#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{

}

void Camera::Move(glm::vec3 move)
{
    matrix = glm::translate(matrix, -move);
}

void Camera::Translate(glm::vec3 translation)
{
    matrix = matrix * glm::translate(glm::mat4(), -translation);
}

float* Camera::getDataPtr()
{
    return glm::value_ptr(matrix);
}