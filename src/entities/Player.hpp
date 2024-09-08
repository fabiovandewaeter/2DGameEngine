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

    void handleEvents(SDL_Event *event);
    
    void setPosition(int x, int y);

private:
};

#endif