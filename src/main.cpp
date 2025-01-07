#ifdef PROFILER
#include "tracy/Tracy.hpp"
#endif

#include "Game.hpp"

#include "systems/TickManager.hpp"

Game game;

int main(int argc, char *argv[])
{

    unsigned int width = 800;
    unsigned int height = 600;
    unsigned int UPS = 60;
    int vsync = 1;
    if (argc == 2)
    {
        UPS = std::atoi(argv[1]);
    }
    if (argc >= 3)
    {
        width = std::atoi(argv[1]);
        height = std::atoi(argv[2]);
    }
    if (argc >= 4)
    {
        UPS = std::atoi(argv[3]);
    }
    if (argc >= 5)
    {
        vsync = std::atoi(argv[4]);
    }
    std::cout << "Window width: " << width << std::endl;
    std::cout << "Window height: " << height << std::endl;
    std::cout << "UPS: " << UPS << std::endl;
    std::cout << "vsync: " << (vsync ? "true" : "false") << std::endl;

    game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false, vsync);
    game.setUPS(UPS);

    TickManager *tickManager = TickManager::getInstance();

    while (game.running())
    {
        tickManager->setFrameStart();
        game.handleEvents();
        game.update();
        game.render();

        tickManager->handleTickSpeed(game.getFrameDelay());
#ifdef PROFILER
        FrameMark;
#endif
    }

    game.clean();
    return 0;
}
