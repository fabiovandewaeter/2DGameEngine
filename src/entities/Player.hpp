#ifndef player_hpp
#define player_hpp

#include <SDL_render.h>
#include "../LTexture.hpp"

class Player
{
public:
    Player();
    ~Player();

    bool update();
    void init(LTexture *texture, SDL_Rect position);
    void handleEvents(SDL_Event *event);
    bool move();
    void render(SDL_Renderer *renderer);

    void setVelocity(int velX, int velY);
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);

private:
    LTexture *texture;
    int velX, velY;
    SDL_Rect position;
};

#endif