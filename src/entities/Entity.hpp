#ifndef entity_hpp
#define entity_hpp

#include <SDL_render.h>
#include "../LTexture.hpp"

class Entity
{
public:
    Entity();
    ~Entity();

    void init(LTexture *texture, int positionX, int positionY);
    bool update();
    bool move();
    void render(SDL_Renderer *renderer, int cameraX, int cameraY);

    void setVelocity(int velX, int velY);
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);

    int getPositionX();
    int getPositionY();
    LTexture* getTexture();

protected:
    LTexture *texture;
    int velX, velY;
    int positionX, positionY;
    int VELOCITY;
};

#endif