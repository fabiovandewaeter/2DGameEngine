#ifndef tick_manager_hpp
#define tick_manager_hpp

#include "SDL2/SDL_stdinc.h"

class TickManager
{
public:
    TickManager();
    ~TickManager();

    void waitTick(const Uint64 &gameFrameDelay);
    Uint64 getNormalizedTick();
    void setFrameStart();
    Uint64 getTicks();

private:
    Uint64 ticks;
    Uint64 frequency;
    Uint64 frameStart;
};

#endif
