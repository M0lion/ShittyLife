#include "Camera.h"
#include "Globals.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera()
{
    pos[3] = 1;
    yaw = 0;
    pitch = 0;
}

Camera::~Camera()
{

}

void Camera::Move(glm::vec3 move)
{
    //matrix = glm::translate(matrix, -move);
    pos += getRotation() * glm::vec4(move, 1);
    pos.w = 1;

    isUpToDate = false;
}

void Camera::Translate(glm::vec3 translation)
{
    //matrix = matrix * glm::translate(glm::mat4(), -translation);
    pos += glm::vec4(translation, 0);

    isUpToDate = false;
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
    rot = glm::rotate(rot, yaw, glm::vec3(0,1,0));
    rot = glm::rotate(rot, pitch, glm::vec3(1,0,0));
    
    return rot;
}

void Camera::update()
{
    matrix = getRotation();

    //translation
    matrix = glm::translate(matrix, glm::vec3(-pos));

    isUpToDate = true;
}