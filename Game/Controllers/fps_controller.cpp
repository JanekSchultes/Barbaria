#include "fps_controller.h"

Camera* FPSController::camera = nullptr;
bool FPSController::first_movement = true;
double FPSController::lastX = 0.0f;
double FPSController::lastY = 0.0f;
bool forward_pressed = false;
bool backward_pressed = false;
bool left_pressed = false;
bool right_pressed = false;

void FPSControllerData::setupCamera(Camera& camera) {
    FPSController::camera = &camera;
}

FPSController::FPSController() {

}

FPSController::FPSController(InputHandler* input_handler) : Controller(input_handler) {
    input_handler->initKeyCallback(Input::KeyCallback(brumm, Input::KeyAction::PRESS), 256);
    input_handler->initKeyCallback(Input::KeyCallback(forward_press, Input::KeyAction::PRESS), 87);
    input_handler->initKeyCallback(Input::KeyCallback(backward_press, Input::KeyAction::PRESS), 83);
    input_handler->initKeyCallback(Input::KeyCallback(left_press, Input::KeyAction::PRESS), 65);
    input_handler->initKeyCallback(Input::KeyCallback(right_press, Input::KeyAction::PRESS), 68);
    input_handler->initKeyCallback(Input::KeyCallback(forward_release, Input::KeyAction::RELEASE), 87);
    input_handler->initKeyCallback(Input::KeyCallback(backward_release, Input::KeyAction::RELEASE), 83);
    input_handler->initKeyCallback(Input::KeyCallback(left_release, Input::KeyAction::RELEASE), 65);
    input_handler->initKeyCallback(Input::KeyCallback(right_release, Input::KeyAction::RELEASE), 68);
    input_handler->initMouseCallback(Input::MouseCallback(mouse_movement));
}

void FPSController::mouse_movement(double xpos, double ypos) {
    if (first_movement) {
        lastX = xpos;
        lastY = ypos;
        first_movement = false;
        return;
    }
    double xOffset = xpos - lastX;
    double yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera->processMouseMovement(xOffset, yOffset);
}

void FPSController::forward_press() {
    forward_pressed = true;
}

void FPSController::backward_press() {
    backward_pressed = true;
}

void FPSController::left_press() {
    left_pressed = true;
}

void FPSController::right_press() {
    right_pressed = true;
}

void FPSController::forward_release() {
    forward_pressed = false;
}

void FPSController::backward_release() {
    backward_pressed = false;
}

void FPSController::left_release() {
    left_pressed = false;
}

void FPSController::right_release() {
    right_pressed = false;
}

void FPSController::update(){

    if (right_pressed) camera->moveRight();
    if (left_pressed) camera->moveLeft();
    if (forward_pressed) camera->moveForward();
    if (backward_pressed) camera->moveBackward();
}


void FPSController::brumm() {
    std::cout << "Brumm\n";
}
