#include "Controller.h"

Controller::Controller() {

}

Controller::Controller(InputHandler* input_handler) {
}

void Controller::reset() {
    pressed_keys.clear();
}
