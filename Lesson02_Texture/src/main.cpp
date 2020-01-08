#include <iostream>
#include "Game.h"


int main()
{
    Game game;
    if (!game.Init()) {
        std::cout << "Failed to initialize!" << std::endl;
    } else {
        while (game.IsRunning()) {
            game.HandleEvents();
            game.Update();
            game.Render();
        }
    }
    game.Clean();
    return 0;
}

