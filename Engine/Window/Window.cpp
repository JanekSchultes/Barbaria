#include "Window.h"

bool Window::opengl_initialized = false;

Window::Window() {
    glfw_window = nullptr;
}

Window::Window(std::string title, float size_x, float size_y) {
    if (!opengl_initialized) {
        if (!glfwInit()) {
            std::cout << "Glew Initialization failed!\n";
        }
        //glfwSetErrorCallback(glfw_error_callback);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfw_window = glfwCreateWindow(size_x, size_y, title.c_str(), nullptr, nullptr);
    if (!glfw_window) {
        std::cout << "Game window creation failed\n";
    }

    glfwMakeContextCurrent(glfw_window);
    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetKeyCallback(game_window, key_callback);

    if (!opengl_initialized) {
        if (glewInit() != GLEW_OK) {
            std::cout << "Failed OpenGL initialization\n";
        }
        else {
            opengl_initialized = true;
        }
    }

    //glDebugMessageCallback(glDebugCallback, 0);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

GLFWwindow* Window::getWindowPointer() {
    return glfw_window;
}

void glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "[GLDBG] " << message << "\n";
}

void glfw_error_callback(int error, const char* description) {
    std::cout << "A GLFW error occurred!\n";
    std::cout << description << '\n';
    throw std::runtime_error("Could not continue due to fatal GLFW error.");
}
