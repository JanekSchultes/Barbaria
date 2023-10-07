#define STB_IMAGE_IMPLEMENTATION
#include "Game/Game.h"


#include "Barbaria.h"

int main() {
    std::cout << "Starting Barbaria...\n";
    std::cout << "test\n";
    Game sw{};

    while (true) {
        sw.game_loop();
    }
}

