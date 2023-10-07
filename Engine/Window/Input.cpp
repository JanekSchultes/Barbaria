#include "Input.h"

void doNothing() {}

std::multimap<int, Input::KeyCallback> InputHandler::current_callbacks = { {0, Input::KeyCallback()} };
Input::MouseCallback InputHandler::current_mouse_callback = Input::MouseCallback();

InputHandler::InputHandler() {
    associated_window = nullptr;
}

InputHandler::InputHandler(Window* listened_window) {
    associated_window = listened_window;
}

void InputHandler::bind() {
    glfwSetKeyCallback(associated_window->getWindowPointer(), keyCallback);
    glfwSetCursorPosCallback(associated_window->getWindowPointer(), mouseCallback);
    updateCallbacks();
}

void InputHandler::updateCallbacks() {
    current_callbacks = callbacks;
}

void InputHandler::initMouseCallback(Input::MouseCallback callback) {
    current_mouse_callback = callback;
}

void InputHandler::keyCallback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
    auto searcher = current_callbacks.equal_range(key);
    for (auto it = searcher.first; it != searcher.second; ++it) {
        if (it->second.isAction(action)) {
            it->second.callback_function();
            return;
        }
    }
}

void InputHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    current_mouse_callback.callback_function(xpos, ypos);
}

void InputHandler::initKeyCallback(Input::KeyCallback callback, int key) {
    callbacks.insert({ key, callback });
}

namespace Input {
    KeyCallback::KeyCallback() {
        callback_function = nullptr;
    }

    KeyCallback::KeyCallback(std::function<void()> func, KeyAction action) {
        callback_function = func;
        callback_action = action;
    }

    bool KeyCallback::isAction(int action) {
        if (action == GLFW_PRESS && callback_action == KeyAction::PRESS) return true;
        if (action == GLFW_RELEASE && callback_action == KeyAction::RELEASE) return true;
        return false;
    }

    MouseCallback::MouseCallback() {
        callback_function = nullptr;
    }

    MouseCallback::MouseCallback(std::function<void(double xpos, double ypos)> func) {
        callback_function = func;
    }
}
