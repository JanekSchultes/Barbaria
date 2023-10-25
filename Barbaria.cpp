#define STB_IMAGE_IMPLEMENTATION
#include "Game/Game.h"


#include "Barbaria.h"

int main() {
    std::cout << "Starting Barbaria...\n";
    std::cout << "test\n";
    Game sw{};
    sw.render = true;

    std::thread compute_thread(&Game::compute_loop, &sw);
    //std::thread render_thread(&Game::game_loop, &sw);
    sw.game_loop();

    /*while (true) {
        sw.game_loop();
    }*/

    compute_thread.join();
    //render_thread.join();
}

