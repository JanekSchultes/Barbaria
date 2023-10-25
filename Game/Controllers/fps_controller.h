#ifndef FPS_CONTROLLER
#define FPS_CONTROLLER

#include <iostream>
#include <mutex>

#include "Controller.h"
#include "../../Engine/Engine.h"

namespace FPSControllerData {
    void setupCamera(Camera& camera);
}

class FPSController : public Controller {
public:
    FPSController();
    FPSController(InputHandler* input_handler);
    static void brumm();
    static void forward_press();
    static void backward_press();
    static void left_press();
    static void right_press();
    static void forward_release();
    static void backward_release();
    static void left_release();
    static void right_release();
    static void update(); 
    static void mouse_movement(double xpos, double ypos);
    static Camera* camera;
    static bool first_movement;
    static double lastX;
    static double lastY;

    /*static bool forward_pressed;
    static bool backward_pressed;
    static bool left_pressed;
    static bool right_pressed; */
private:
};

#endif
