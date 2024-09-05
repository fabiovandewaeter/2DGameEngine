#ifndef player_hpp
#define player_hpp

#include <SDL_render.h>
#include "../LTexture.hpp"
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player();
    ~Player();

    void render(SDL_Renderer *renderer, double scale);

private:
};

#endif