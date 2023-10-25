#include "Engine.h"

unsigned int depth_frame_buffer = 0;
unsigned int depth_rbo = 0;

/* std::map<std::string, Window> Engine::windows = std::vector<Window>(0);
Window Engine::active_window = Window();
std::map<std::string, InputHandler> Engine::input_handlers() = std::vector<InputHandler>(0);
InputHandler Engine::active_input_handler = InputHandler();
std::map<std::string, Camera> Engine::cameras() = std::vector<Camera>(0);
Camera Engine::active_camera = Camera();
std::map<std::string, View> Engine::views() = std::vector<View>(0);
View Engine::active_view = View();
std::map<std::string, Shader> Engine::shaders() = std::vector<Shader>(0);
Shader Engine::active_shader = Shader();
std::vector<ChunkRender> Engine::chunk_renderers = std::vector<ChunkRender>(0);
Texture Engine::block_atlas = Texture(); */

namespace Engine {
    std::map<std::string, Window> windows;
    Window active_window = Window();
    std::map<std::string, InputHandler> input_handlers;
    InputHandler active_input_handler = InputHandler();
    std::map<std::string, Camera> cameras;
    Camera active_camera = Camera();
    std::map<std::string, View> views;
    View active_view = View();
    std::map<std::string, Shader> shaders;
    Shader active_shader = Shader();
    Texture block_atlas = Texture();
}

void Engine::init() {
    glGenFramebuffers(1, &depth_frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, depth_frame_buffer);
    glGenRenderbuffers(1, &depth_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH, 1920, 1080);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Engine::recalculateDepths() {
    //glBindFramebuffer(GL_FRAMEBUFFER, depth_frame_buffer);
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    /*glClear(GL_DEPTH_BUFFER_BIT);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    auto it = shaders.find("precalc_shader");
    it->second.bind();
    it->second.pushMatrix4f(active_view.getMatrix(), "projectionMatrix");
    active_camera.update();
    it->second.pushMatrix4f(active_camera.getViewMatrix(), "viewMatrix");

    glDepthMask(GL_TRUE);
    VoxelRender::render();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); */
}

void Engine::prepareRendering(float ambient_strength) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.3f, 0.7f, 1.0f, 0.2f);
    active_shader.bind();
    active_shader.pushMatrix4f(active_view.getMatrix(), "projectionMatrix");
    active_shader.pushMatrix4f(active_camera.getViewMatrix(), "viewMatrix");
    active_shader.pushFloat(ambient_strength, "ambientLight");
    block_atlas.bind();
}

void Engine::finishRendering() {
    glfwSwapBuffers(active_window.getWindowPointer());
    glfwPollEvents();
}

void Engine::destroy() {
    for (auto it = windows.begin(); it != windows.end(); ++it) {
        glfwDestroyWindow(it->second.getWindowPointer());
    }
    glfwTerminate();
}

void Engine::registerWindow(Window window, std::string name) {
    windows.insert({ name, window });
}

void Engine::registerInputHandler(InputHandler input_handler, std::string name) {
    input_handlers.insert({ name, input_handler });
}

void Engine::registerCamera(Camera camera, std::string name) {
    cameras.insert({ name, camera });
}

void Engine::registerView(View view, std::string name) {
    views.insert({ name, view });
}

void Engine::registerShader(Shader shader, std::string name) {
    shaders.insert({ name, shader });
}

void Engine::activeWindow(std::string name) {
    auto it = windows.find(name);
    if (it == windows.end()) throw std::invalid_argument("Element does not exist");
    active_window = it->second;
}

void Engine::activeInputHandler(std::string name) {
    auto it = input_handlers.find(name);
    if (it == input_handlers.end()) throw std::invalid_argument("Element does not exist");
    active_input_handler = it->second;
    active_input_handler.bind();
}

void Engine::activeCamera(std::string name) {
    auto it = cameras.find(name);
    if (it == cameras.end()) throw std::invalid_argument("Element does not exist");
    active_camera = it->second;
}

void Engine::activeView(std::string name) {
    auto it = views.find(name);
    if (it == views.end()) throw std::invalid_argument("Element does not exist");
    active_view = it->second;
}

void Engine::activeShader(std::string name) {
    auto it = shaders.find(name);
    if (it == shaders.end()) throw std::invalid_argument("Element does not exist");
    active_shader = it->second;
    active_shader.bind();
}

void Engine::loadBlockAtlas(std::string block_atlas_path) {
    block_atlas = Texture(block_atlas_path.c_str());
}

Camera& Engine::getActiveCamera() {
    return active_camera;
}
