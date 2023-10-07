#ifndef INPUT
#define INPUT

#include <functional>
#include <map>

#include "Window.h"

namespace Input {
    enum class KeyAction {
        PRESS,
        RELEASE
    };

    struct KeyCallback {
        KeyCallback();
        KeyCallback(std::function<void()> func, KeyAction action);
        bool isAction(int action);
        std::function<void()> callback_function;
        KeyAction callback_action;
    };

    struct MouseCallback {
        MouseCallback();
        MouseCallback(std::function<void(double xpos, double ypos)> func);
        std::function<void(double xpos, double ypos)> callback_function;
    };
}

class InputHandler {
public:
    InputHandler();
    InputHandler(Window* listened_window);
    void bind();
    void updateCallbacks();
    static void keyCallback(GLFWwindow* window, int key, int scan_code, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    void initKeyCallback(Input::KeyCallback callback, int key);
    void initMouseCallback(Input::MouseCallback callback);
private:
    Window* associated_window;
    static std::multimap<int, Input::KeyCallback> current_callbacks;
    std::multimap<int, Input::KeyCallback> callbacks;
    static Input::MouseCallback current_mouse_callback;
};

#endif
