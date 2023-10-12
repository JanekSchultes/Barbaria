#ifndef ENGINE
#define ENGINE

#include <vector>
#include <string>
#include <map>
#include <GL/glew.h>

#include "Rendering/Camera.h"
#include "Rendering/Shader.h"
#include "Rendering/View.h"

#include "Window/Window.h"
#include "Window/Input.h"

#include "Object/Texture.h"
#include "Object/voxel_render.h"

namespace Engine {
    void init();
    void destroy();

    void recalculateDepths();
    void renderChunks(float ambient_strength);

    void registerWindow(Window window, std::string name);
    void registerInputHandler(InputHandler input_handler, std::string name);
    void registerCamera(Camera camera, std::string name);
    void registerView(View view, std::string name);
    void registerShader(Shader shader, std::string name);

    void activeWindow(std::string name);
    void activeInputHandler(std::string name);
    void activeCamera(std::string name);
    void activeView(std::string name);
    void activeShader(std::string name);

    Camera& getActiveCamera();

    void loadBlockAtlas(std::string block_atlas_path);
    /* std::map<std::string, Window> windows;
    Window active_window;
    std::map<std::string, InputHandler> input_handlers;
    InputHandler active_input_handler;
    std::map<std::string, Camera> cameras;
    Camera active_camera;
    std::map<std::string, View> views;
    View active_view;
    std::map<std::string, Shader> shaders;
    Shader active_shader;
    std::vector<ChunkRender> chunk_renderers = std::vector<ChunkRender>(0);
    Texture block_atlas; */
}

#endif
