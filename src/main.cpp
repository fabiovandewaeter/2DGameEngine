#include "Game.hpp"

Game game;
Uint64 frequency = SDL_GetPerformanceFrequency();

Uint64 getNormalizedTick()
{
    return SDL_GetPerformanceCounter() / (frequency / 10000000);
}

// if the loop lasted less than on frame at the speed of game.fixedUPS, wait until the end
void handleTickSpeed(Uint64 &frameStart)
{
    Uint64 deltaTime = getNormalizedTick() - frameStart;

    if (deltaTime < game.getFrameDelay())
    {
        Uint64 remainingTime = game.getFrameDelay() - deltaTime;
        if (remainingTime >= 20000) // 20000 = 2ms because SDL_Delay(1) wait more than 1 ms ; the last millisecond is handled by the more precise while loop
        {
            SDL_Delay((remainingTime / 10000) - 1); // -1 because of the margin of error or SDL_Delay()
        }
        deltaTime = getNormalizedTick() - frameStart;
        while (deltaTime < game.getFrameDelay()) // wait for sub-millisecond duration but is CPU heavy
        {
            deltaTime = getNormalizedTick() - frameStart;
        }
    }
}

int main(int argc, char *argv[])
{

    int width = 800;
    int height = 600;
    unsigned int UPS = 60;
    std::cout << argc << " " << argv[1] << std::endl;
    if (argc == 2){
        UPS = std::atoi(argv[1]);
    }
    else if (argc == 4)
    {
        width = std::atoi(argv[1]);
        height = std::atoi(argv[2]);
        UPS = std::atoi(argv[3]);
    }
    std::cout << "Window width: " << width << std::endl;
    std::cout << "Window height: " << height << std::endl;

    game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false);
    // game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);
    game.setUPS(UPS);

    while (game.running())
    {
        Uint64 frameStart = getNormalizedTick();
        game.handleEvents();
        game.update();
        game.render();

        handleTickSpeed(frameStart);
    }

    game.clean();
    return 0;
}
