#include "Game.hpp"

Game game;
Uint64 frequency = SDL_GetPerformanceFrequency();

Uint64 getNormalizedTick(){
    return SDL_GetPerformanceCounter() / (frequency/10000000);
}

// if the loop lasted less than on frame at the speed of game.fixedUPS, wait until the end
void handleTickSpeed(Uint64 &frameStart)
{
    Uint64 deltaTime = getNormalizedTick() - frameStart;
    
    if (deltaTime < game.frameDelay)
    {
        Uint64 remainingTime = game.frameDelay - deltaTime;
        if (remainingTime >= 20000) // 20000 = 2ms because SDL_Delay(1) wait more than 1 ms ; the last millisecond is handled by the more precise while loop
        {
            SDL_Delay((remainingTime / 10000) - 1); // -1 because of the margin of error or SDL_Delay()
        }
        deltaTime = getNormalizedTick() - frameStart;
        while (deltaTime < game.frameDelay) // wait for sub-millisecond duration but is CPU heavy
        {
            deltaTime = getNormalizedTick() - frameStart;
        }
    }
}

int main(int argc, char *argv[]) {
    game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    game.setUPS(60);

    while (game.running()){
        Uint64 frameStart = getNormalizedTick();
        game.handleEvents();
        game.update();
        game.render();

        handleTickSpeed(frameStart);
    }
    
    game.clean();
    return 0;
}