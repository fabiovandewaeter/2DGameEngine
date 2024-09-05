
#ifndef entity_hpp
#define entity_hpp

#include <SDL_render.h>
#include "../LTexture.hpp"

class Entity
{
public:
    Entity();
    ~Entity();

    bool update();
    void init(LTexture *texture, SDL_Rect position);
    void handleEvents(SDL_Event *event);
    bool move();
    void render(SDL_Renderer *renderer);

    void setVelocity(int velX, int velY);
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);

protected:
    LTexture *texture;
    int velX, velY;
    SDL_Rect position;

    int VELOCITY;
    int SPRINT_VELOCITY;
    // 1 if false and SPRINT_VELOCITY if true
    int sprint;
    int leftVelX, rightVelX, upVelY, downVelY;
};

#endif