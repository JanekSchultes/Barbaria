#include "Game.h"

double lastRenderTime = 0.0;
double lastTickTime = 0.0;

Game::Game() {
    Engine::init();
    Engine::registerWindow(game_window, "game_window");
    Engine::activeWindow("game_window");
    Engine::registerInputHandler(fps_input_handler, "fps_input_handler");
    Engine::activeInputHandler("fps_input_handler");
    Engine::registerCamera(fps_camera, "fps_camera");
    Engine::activeCamera("fps_camera");
    Engine::registerShader(fps_shader, "fps_shader");
    Engine::registerShader(precalc_shader, "precalc_shader");
    Engine::activeShader("fps_shader");
    Engine::registerView(fps_view, "fps_view");
    Engine::activeView("fps_view");
    Engine::loadBlockAtlas("assets/textures/block_atlas.png");

    FPSControllerData::setupCamera(Engine::getActiveCamera());

    game_world.loadInitialChunks({ 0.0f, 0.0f });
    lastRenderTime = glfwGetTime();
    lastTickTime = glfwGetTime();
}

void Game::game_loop() {

    if ((glfwGetTime() - lastRenderTime) > 0.015) {
        fps_controller.update();
        Engine::renderChunks(game_world.ambient_strength);
        lastRenderTime = glfwGetTime();
    }

    if ((glfwGetTime() - lastTickTime) > 0.015) {
        game_world.doTick();
        lastTickTime = glfwGetTime();
    }

    /*if((glfwGetTime() - lastInputTime) > 0.45) {
        fps_controller.update();
        input_thread = std::thread(Engine::recalculateDepths);
        lastInputTime = 0.0;
        input_thread.join();
    }*/
}
