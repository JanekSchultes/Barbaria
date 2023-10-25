#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Utils/math_utils.h"

#include <iostream>
#include <mutex>

#define MAX_PITCH_ANGLE 89

class Camera {
public:
    Camera();
    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void setPosition(glm::vec3 pos);
    static void processMouseMovement(float xOffSet, float yOffSet);
    void update();
    glm::vec3 getCameraPosition();
    glm::vec3 getCameraFront();
    glm::mat4 getViewMatrix();
protected:
private:
    static float movementSpeed;
    static float mouseSensitivity;
    static float yaw;
    static float pitch;
    glm::vec3 cameraPosition;
    glm::vec3 worldUP;
    glm::vec3 cameraFront;
    glm::vec3 cameraUP;
    glm::vec3 cameraRight;
    glm::mat4 viewMatrix;
};

#endif
