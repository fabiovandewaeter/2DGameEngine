#ifndef player_hpp
#define player_hpp

#include <SDL_render.h>
#include "../Texture.hpp"
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player();
    ~Player();

    void render2(SDL_Renderer *renderer, double scale);

private:
};

#endif