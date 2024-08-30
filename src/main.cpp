#include "Game.hpp"

Game game;
Uint64 deltaTime;

// if the loop lasted less than on frame at the speed of game.fixedUPS, wait until the end
void handleTickSpeed(Uint64 &frameStart)
{
    deltaTime = SDL_GetPerformanceCounter() - frameStart;
    Uint64 remainingTime = game.frameDelay - deltaTime;
    Uint64 timeSlept = 0;
    
    // SDL_Delay() can only wait milliseconds but consumes little CPU
    if (deltaTime < game.frameDelay && remainingTime >= 20000) {
        unsigned int msSlept = remainingTime / 10000;
        Uint64 startTimeSlept = SDL_GetPerformanceCounter();
        SDL_Delay(msSlept);
        timeSlept = (SDL_GetPerformanceCounter() - startTimeSlept);
        if (timeSlept > game.frameDelay) {
            remainingTime = 0;
        }
        else {
            remainingTime = game.frameDelay - timeSlept;
        }
        std::cout << "timeSlept: " << timeSlept << std::endl;
    }
    deltaTime = SDL_GetPerformanceCounter() - frameStart;
    // can wait for sub-millisecond duration but is CPU heavy
    while (deltaTime < game.frameDelay)
    {
        deltaTime = SDL_GetPerformanceCounter() - frameStart;
    }
}

int main(int argc, char *argv[]) {
    game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    game.changeUPS(1200);

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