#ifndef GAME
#define GAME

#include "../Engine/Engine.h"
#include "Controllers/fps_controller.h"
#include "World/World.h"

#include <GLFW/glfw3.h>
#include <thread>
#include <mutex>
#include <chrono>

#define GAME_TITLE "Barbaria"
#define WINDOW_SIZE_X 1920.0f
#define WINDOW_SIZE_Y 1080.0f

class Game {
public:
    Game();
    void game_loop();
    void compute_loop();
    bool render = false;
private:
    Window game_window = Window(GAME_TITLE, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    InputHandler fps_input_handler = InputHandler(&game_window);
    Camera fps_camera;
    FPSController fps_controller = FPSController(&fps_input_handler);
    Shader fps_shader = Shader("assets/shaders/voxel_shader.vs", "assets/shaders/voxel_shader.fs");
    Shader precalc_shader = Shader("assets/shaders/voxel_shader_precalc.vs", "assets/shaders/voxel_shader_precalc.fs");
    PerspectiveView fps_view = PerspectiveView(45.0f, WINDOW_SIZE_X / WINDOW_SIZE_Y, 0.01f, 100.0f);
    World game_world = World();
};

#endif
