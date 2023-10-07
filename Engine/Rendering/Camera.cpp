#include "Camera.h"

float Camera::movementSpeed = 0.05f;
float Camera::mouseSensitivity = 0.01f;
float Camera::yaw = 90.0f;
float Camera::pitch = 0.0f;

Camera::Camera() {
    cameraPosition = glm::vec3(2.0f, 2.0f, 5.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUP = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::vec3(0.0f);
    worldUP = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
}

void Camera::setPosition(glm::vec3 pos) {
    cameraPosition = pos;
}

void Camera::moveForward() {
    cameraPosition += movementSpeed * cameraFront;
}

void Camera::moveBackward() {
    cameraPosition -= movementSpeed * cameraFront;
}

void Camera::moveRight() {
    cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUP)) * movementSpeed;
}

void Camera::moveLeft() {
    cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUP)) * movementSpeed;
}

void Camera::update() {
    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront);
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUP));
    cameraUP = glm::normalize(glm::cross(cameraRight, cameraFront));
    viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUP);
}

glm::mat4 Camera::getViewMatrix() {
    return viewMatrix;
}

glm::vec3 Camera::getCameraPosition() {
    return cameraPosition;
}

glm::vec3 Camera::getCameraFront() {
    return cameraFront;
}

void Camera::processMouseMovement(float xOffSet, float yOffSet) {
    xOffSet *= mouseSensitivity;
    yOffSet *= mouseSensitivity;
    yaw += xOffSet;
    pitch += yOffSet;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}
