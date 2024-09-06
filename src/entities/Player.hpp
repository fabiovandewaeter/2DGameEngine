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
    void render2(SDL_Renderer *renderer, double scale);
    
    void setPosition(int x, int y);

private:
};

#endif