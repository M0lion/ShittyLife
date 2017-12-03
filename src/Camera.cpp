#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{

}

void Camera::Move(glm::vec3 move)
{
    //matrix = glm::translate(matrix, -move);
    glm::mat4 moveMat = glm::translate(glm::mat4(), move);
    moveMat *= getRotation();
    pos = moveMat * pos;
}

void Camera::Translate(glm::vec3 translation)
{
    //matrix = matrix * glm::translate(glm::mat4(), -translation);
    pos += glm::vec4(translation, 0);
}

float* Camera::getDataPtr()
{
    if(!isUpToDate)
        update();

    return glm::value_ptr(matrix);
}

glm::mat4 Camera::getRotation()
{
    glm::mat4 rot = glm::mat4();

    //rotation
    rot = glm::rotate(matrix, yaw, glm::vec3(0,1,0));
    rot = glm::rotate(matrix, pitch, glm::vec3(1,0,0));
    
    return rot;
}

void Camera::update()
{
    matrix = getRotation();

    //translation
    matrix = glm::translate(matrix, glm::vec3(pos));

    isUpToDate = true;
}