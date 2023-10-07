#ifndef WINDOW
#define WINDOW

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void glfw_error_callback(int error, const char* description);

class Window {
public:
    Window();
    Window(std::string title, float size_x, float size_y);
    GLFWwindow* getWindowPointer();
    static bool opengl_initialized;
private:
    GLFWwindow* glfw_window;
};

#endif
