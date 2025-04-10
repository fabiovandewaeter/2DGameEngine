#include "Game.hpp"

int main(int argc, char *argv[])
{
    unsigned int windowWidth = 1280;
    unsigned int windowHeight = 720;
    unsigned int UPS = 60;
    int vsync = 1;
    if (argc == 2)
    {
        UPS = std::atoi(argv[1]);
    }
    if (argc >= 3)
    {
        windowWidth = std::atoi(argv[1]);
        windowHeight = std::atoi(argv[2]);
    }
    if (argc >= 4)
    {
        UPS = std::atoi(argv[3]);
    }
    if (argc >= 5)
    {
        vsync = std::atoi(argv[4]);
    }

    Game *game = new Game("TestEngine", windowWidth, windowHeight, false, vsync, UPS);
    game->run(); // Game loop
    delete game;
    return 0;
}
