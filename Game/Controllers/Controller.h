#ifndef CONTROLLER
#define CONTROLLER

#include <vector>

#include "../../Engine/Engine.h"

class Controller {
public:
    Controller();
    Controller(InputHandler* input_handler);
    void reset();
    void activate();
protected:
    std::vector<char> pressed_keys;
};

#endif
