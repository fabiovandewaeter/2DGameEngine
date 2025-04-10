#include "systems/core/TickManager.hpp"

#include "SDL2/SDL_timer.h"

TickManager::TickManager()
{
    ticks = 0;
    frequency = SDL_GetPerformanceFrequency();
}
TickManager::~TickManager() {}

Uint64 TickManager::getNormalizedTick() { return SDL_GetPerformanceCounter() / (frequency / 10000000); }
void TickManager::setFrameStart() { frameStart = getNormalizedTick(); }
Uint64 TickManager::getTicks() { return ticks; }

// if the loop lasted less than on frame at the speed of game.fixedUPS, wait until the end
void TickManager::waitTick(const Uint64 &gameFrameDelay)
{
    Uint64 deltaTime = getNormalizedTick() - frameStart;

    if (deltaTime < gameFrameDelay)
    {
        Uint64 remainingTime = gameFrameDelay - deltaTime;
        if (remainingTime >= 20000) // 20000 = 2ms because SDL_Delay(1) wait more than 1 ms ; the last millisecond is handled by the more precise while loop
        {
            SDL_Delay((remainingTime / 10000) - 1); // -1 because of the margin of error or SDL_Delay()
        }
        deltaTime = getNormalizedTick() - frameStart;
        while (deltaTime < gameFrameDelay) // wait for sub-millisecond duration but is CPU heavy
        {
            deltaTime = getNormalizedTick() - frameStart;
        }
    }
    ticks++;
}
