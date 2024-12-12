#ifndef player_hpp
#define player_hpp

#define SPRINT_MULTIPLIER 5

#include <SDL2/SDL.h>
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(Texture *texture, const SDL_Rect& hitBox, const int& HP);
    ~Player();

    void handleEvents(SDL_Event *event);

    void setPosition(const int& x, const int& y);

private:
};

#endif