#include "Game.hpp"

Game game;
Uint64 deltaTime;

// if the loop lasted less than on frame at the speed of game.fixedUPS, wait until the end
void handleTickSpeed(Uint64 &frameStart)
{
    deltaTime = SDL_GetPerformanceCounter() - frameStart;
    Uint64 remainingTime = game.frameDelay - deltaTime;
    Uint64 timeSlept = 0;
    
    if (deltaTime < game.frameDelay)
    {
        if (remainingTime >= 20000) // 20000 = 2ms because SDL_Delay(1) wait more than 1 ms ; the last millisecond is handled by the more precise while loop
        {
            SDL_Delay((remainingTime / 10000) - 1); // -1 because of the margin of error or SDL_Delay()
        }
        deltaTime = SDL_GetPerformanceCounter() - frameStart;
        while (deltaTime < game.frameDelay) // wait for sub-millisecond duration but is CPU heavy
        {
            deltaTime = SDL_GetPerformanceCounter() - frameStart;
        }
    }
}

int main(int argc, char *argv[]) {
    game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    game.setUPS(60);

    while (game.running()){
        Uint64 frameStart = SDL_GetPerformanceCounter() ;
        game.handleEvents();
        game.update();
        game.render();

        handleTickSpeed(frameStart);
    }
    
    game.clean();
    return 0;
}