#ifndef entity_hpp
#define entity_hpp

#include <SDL_render.h>
#include "../LTexture.hpp"

class Entity
{
public:
    Entity();
    ~Entity();

    void init(LTexture *texture, SDL_Rect position);
    void handleEvents(SDL_Event *event);
    bool update();
    bool move();
    void render(SDL_Renderer *renderer, int cameraX, int cameraY);

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