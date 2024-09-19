#ifndef player_hpp
#define player_hpp

#define SPRINT_MULTIPLIER 5

#include <SDL.h>
#include <SDL_render.h>
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player();
    ~Player();

    void init(Texture *texture, SDL_Rect hitBox);
    void handleEvents(SDL_Event *event);
    
    void setPosition(int x, int y);

private:
};

#endif