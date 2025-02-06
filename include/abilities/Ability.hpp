#ifndef ability_hpp
#define ability_hpp

#include <vector>
#include <SDL2/SDL_stdinc.h>

class Entity;
class Pattern;
class Effect;
class TickManager;

class Ability
{
public:
    Ability(Pattern *pattern, std::vector<Effect *> effects, Uint64 cooldown, TickManager *tickManager);
    ~Ability();

    void apply(int x, int y);

private:
    Pattern *pattern;
    std::vector<Effect *> effects;
    int cooldown;
    int cooldownStartTick;
    TickManager *tickManager;
};

#endif
